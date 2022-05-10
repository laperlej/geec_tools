"""
18cd442ee1fa03df74517335ed2ed92d:a0f380a52e792f65b96c41ad5fdfd8e8   chr1,-0.091218  chr10,-0.120059 chr11,-0.085029 chr12,0.962397  chr13,0.038357  chr14,0.908901  chr15,-0.060206 chr16,-0.109638 chr17,-0.091413 chr18,0.03692chr19,-0.113141    chr2,0.999374   chr3,-0.076656  chr4,-0.194520  chr5,-0.087904  chr6,0.821275   chr7,-0.099522  chr8,-0.004072  chr9,0.997895   chrX,0.172631   chrY,0.712472
"""

import itertools
import sys
import numpy as np
import json
import pandas as pd


class InputFile(object):
    def __init__(self, file_path):
        self.nameset = set()
        self.files = []
        self.names = []
        self.parse_file(file_path)

    def parse_file(self, file_path):
        try:
            with open(file_path) as list_file:
                for line in list_file:
                    path, name = line.split()
                    if name not in self.nameset:
                        self.nameset.add(name)
                        self.files.append(path)
                        self.names.append(name)
        except IOError:
            pass

    def __getitem__(self, index):
        return self.files[index], self.names[index]


class Matrix(object):
    def __init__(self, labels, matrix_file=None):
        if matrix_file == None:
            self.index = dict(itertools.izip(labels, xrange(len(labels))))
            self.labels = labels
            self.size = len(labels)
            self.matrix = np.zeros((self.size, self.size))
        else:
            self.matrix = pd.read_csv(matrix_file, delimiter='\t', index_col=0, header=0)
            self.labels = self.matrix.columns.values.tolist()
            self.size = len(labels)
            self.index = self.create_index(self.labels)
            self.matrix = self.matrix.as_matrix()
            self.sub_matrix(labels)

    def sub_matrix(self, labels):
        indexes = [self.index[x] for x in labels if x in self.index]
        self.labels = labels
        self.size = len(labels)
        self.matrix = self.matrix[[indexes]][:, indexes]

    def extend(self, labels):
        old_lenght = len(self.labels)
        extra_lenght = len(labels)
        self.labels = labels + self.labels
        self.size = len(self.labels)
        top_extension = np.zeros((extra_lenght, old_lenght))
        left_extension = np.zeros((old_lenght + extra_lenght, extra_lenght))
        self.matrix = np.concatenate((top_extension, self.matrix), axis=0)
        self.matrix = np.concatenate((left_extension, self.matrix), axis=1)
        self.index = self.create_index(self.labels)

    def create_index(self, labels):
        return dict(itertools.izip(labels, xrange(len(labels))))

    def __getitem__(self, labels):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        return self.matrix[x, y]

    def __setitem__(self, labels, value):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        self.matrix[x, y] = value
        self.matrix[y, x] = value

    def convert_labels(self, meta):
        for i in xrange(len(self.labels)):
            token = meta.get("datasets", {}).get(self.labels[i], {})
            if token:
                self.labels[i] = "{0}".format(token.get("file_name", ""))

    def __str__(self):
        s = ""
        s += '\t' + '\t'.join(self.labels) + '\n'
        for i in xrange(self.size):
            s += self.labels[i] + '\t' + '\t'.join(["{0:.4f}".format(v) for v in self.matrix[i]]) + '\n'
        return s

     
class CorrFileParser(object):
    def __init__(self, corr_file_path):
        self.path = corr_file_path

    def make_matrix(self, labels):
        matrix = Matrix(labels)
        self.fill_matrix(labels, matrix)
        return matrix

    def fill_matrix(self, labels, matrix):
        try:
            with open(self.path) as corr_file:
                header = corr_file.readline()
                header = header.strip().split()
                weights = {}
                for chrom in header:
                    chrom = chrom.split(":")
                    weights[chrom[0]] = float(chrom[1])
                for line in corr_file:
                    line = line.split()
                    file1, file2 = line[0].split(':')
                    average = weighted_average(line[1:], weights)
                    matrix[file1, file2] = average
        except IOError:
            pass

def weighted_average(line, weights):
    w_sum = 0.0
    total = 0.0
    for element in line:
        chrom, value = element.split(',')
        total += weights[chrom]
        w_sum += float(value) * weights[chrom]
    return w_sum / total

def main():
    input_file1 = InputFile(LIST_PATH1)
    input_file2 = InputFile(LIST_PATH2)
    matrix = Matrix(input_file2.names, open(PRECALC_PATH))
    matrix.extend(input_file1.names)
    CorrFileParser(CORR_PATH).fill_matrix(input_file1.names, matrix)
    matrix.convert_labels(META)
    with open(OUTPUT_PATH, 'w') as output_file:
        output_file.write(str(matrix))

def listjson2dictjson(old_json):
    new_json = {"datasets":{}}
    for token in old_json.get("datasets", []):
        new_json["datasets"][token["md5sum"]] = token
    return new_json

if __name__ == '__main__':
    if len(sys.argv) < 6 or len(sys.argv) > 7:
        print("usage: python make_matrix.py {list_path} {corr_path} {output_path}")
        exit()
    LIST_PATH1 = sys.argv[1]
    LIST_PATH2 = sys.argv[2]
    CORR_PATH = sys.argv[3]
    PRECALC_PATH = sys.argv[4]
    OUTPUT_PATH = sys.argv[5]
    if len(sys.argv) == 6:
        META = {}
    elif len(sys.argv) == 7:
        META = listjson2dictjson(json.load(open(sys.argv[6])))
    main()