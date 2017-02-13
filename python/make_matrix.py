"""
18cd442ee1fa03df74517335ed2ed92d:a0f380a52e792f65b96c41ad5fdfd8e8   chr1,-0.091218  chr10,-0.120059 chr11,-0.085029 chr12,0.962397  chr13,0.038357  chr14,0.908901  chr15,-0.060206 chr16,-0.109638 chr17,-0.091413 chr18,0.03692chr19,-0.113141    chr2,0.999374   chr3,-0.076656  chr4,-0.194520  chr5,-0.087904  chr6,0.821275   chr7,-0.099522  chr8,-0.004072  chr9,0.997895   chrX,0.172631   chrY,0.712472
"""

import itertools
import sys
import numpy as np
import json


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
    def __init__(self, labels):
        self.index = dict(itertools.izip(labels, xrange(len(labels))))
        self.labels = labels
        self.size = len(labels)
        self.matrix = np.zeros((self.size, self.size))

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
                self.labels[i] = "{0}_{1}".format(token.get("file_name", ""), self.labels[i])


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
        return matrix

def weighted_average(line, weights):
    total = 0.0
    for element in line:
        chrom, value = element.split(',')
        total += float(value) * weights[chrom]
    return total

def main():
    input_file = InputFile(LIST_PATH)
    matrix = CorrFileParser(CORR_PATH).make_matrix(input_file.names)
    matrix.convert_labels(META)
    with open(OUTPUT_PATH, 'w') as output_file:
        output_file.write(str(matrix))

def listjson2dictjson(old_json):
    new_json = {"datasets":{}}
    for token in old_json["datasets"]:
        new_json["datasets"][token["md5sum"]] = token
    return new_json

if __name__ == '__main__':
    if len(sys.argv) < 4 or len(sys.argv) > 5:
        print("usage: python make_matrix.py {list_path} {corr_path} {output_path}")
        exit()
    LIST_PATH = sys.argv[1]
    CORR_PATH = sys.argv[2]
    OUTPUT_PATH = sys.argv[3]
    if len(sys.argv) == 4:
        META = {}
    elif len(sys.argv) == 5:
        META = listjson2dictjson(json.load(open(sys.argv[5])))
    main()
