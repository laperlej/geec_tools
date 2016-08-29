"""scipt used to generate the final output matrix for geff galaxy
"""

import sys
import itertools
import numpy as np


class Matrix(object):
    """represents a geff output matrix
    """
    def __init__(self):
        self.index = {}
        self.labels = []
        self.size = 0
        self.data = None

    def __getitem__(self, labels):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        return self.data[x, y]

    def __setitem__(self, labels, value):
        x_label, y_label = labels
        x = self.index.get(x_label)
        y = self.index.get(y_label)
        self.data[x, y] = value
        self.data[y, x] = value

    def create_from_file(self, file_path):
        with open(file_path) as matrix_file:
            self.labels = matrix_file.readline().strip().split()
            self.size = len(self.labels)
            cols = range(1, len(self.labels))
            self.data = np.loadtxt(file_path, skiprows=1, usecols=cols)
        self._generate_index()

    def create_from_labels(self, labels):
        self.labels = labels
        self.size = len(labels)
        self.data = np.zeros((self.size, self.size))
        self._generate_index()

    def _generate_index(self):
        self.index = dict(itertools.izip(self.labels, xrange(len(self.labels))))

    def completion(self, correlations, matrix, matrix_labels):
        #nx(n+m)
        for correlation_entry in correlations:
            value = correlation_entry.mean()
            labels = correlation_entry.labels
            self[labels] = value
        #mxm
        for i in range(len(matrix_labels)):
            for j in range(i+1):
                labels = [matrix_labels[i], matrix_labels[j]]
                self[labels] = matrix[labels]

    def write(self, path):
        header = "\t{0}\n".format('\t'.join(self.labels))
        with open(path, 'w') as output_file:
            output_file.write(header)
            for i in xrange(self.size):
                line = "{0}\t{1}\n".format(self.labels[i], '\t'.join([str(v) for v in self.data[i]]))
                output_file.write(line)


def correlation_entry_generator(file_path, chrom_sizes): 
    with open(file_path) as correlation_file:
        for line in correlation_file:
            line = line.split()
            labels = line[0].split(':')
            values = []
            weights = []
            for chrom_entry in line[1:]:
                chrom, value = chrom_entry.split(',')
                values.append(float(value))
                weights.append(chrom_sizes.get_weigth(chrom))

            yield CorrelationEntry(labels, values, weights)


class CorrelationEntry(object):
    def __init__(self, labels, values, weights):
        self.labels = labels
        self.values = values
        self.weights = weights

    def mean(self):
        total = 0
        for i in range(len(self.values)):
            total += self.values[i] * self.weights[i]
        return total


class Inputs(object):
    """represents a geff input file
    """
    def __init__(self, file_path):
        self.labels = []
        self.paths = []
        self._parse_file(file_path)

    def _parse_file(self, file_path):
        with open(file_path) as input_file:
            for line in input_file:
                path, label = line.split()
                self.paths.append(path)
                self.labels.append(label)


class ChromSizes(object):
    def  __init__(self, file_path):
        self.weights = {}
        self.chroms = {}
        self._parse_file(file_path)
        self.genome_size = 0
        self._size()
        self.weights = {}
        self._weights()

    def _parse_file(self, file_path):
        with open(file_path) as chrom_sizes:
            for line in chrom_sizes:
                if line:
                    chrom, chrom_size = line.split()
                    self.chroms[chrom] = int(chrom_size)

    def _size(self):
        for chrom_size in self.chroms.itervalues():
            self.genome_size += chrom_size

    def _weights(self):
        for chrom, chrom_size in self.chroms.iteritems():
            self.weights[chrom] = chrom_size/float(self.genome_size)

    def get_weigth(self, index):
        return self.weights[index]

def main():
    chrom_sizes = sys.argv[1]
    list1 = sys.argv[2]
    list2 = sys.argv[3]
    correlation_file = sys.argv[4]
    matrix_file = sys.argv[5]
    output_matrix_path = sys.argv[6]
    chrom_sizes = ChromSizes(chrom_sizes)
    input1 = Inputs(list1)
    input2 = Inputs(list2)
    labels = input1.labels + input2.labels
    correlations = correlation_entry_generator(correlation_file, chrom_sizes)
    pre_calculated_matrix = Matrix()
    pre_calculated_matrix.create_from_file(matrix_file)
    final_matrix = Matrix()
    final_matrix.create_from_labels(labels)
    final_matrix.completion(correlations, pre_calculated_matrix, input2.labels)

    final_matrix.write(output_matrix_path)

if __name__ == '__main__':
    main()
