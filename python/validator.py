import sys
import os
import h5py
import argparse

class InputManager(object):
    def __init__(self, input_file):
        self.input_tokens = []
        self.load(input_file)

    def load(self, input_file):
        for line in input_file:
            line = line.strip().split("\t")
            if line: self.input_tokens.append(line)

    def __iter__(self):
        return iter(self.input_tokens)


class Validator(object):
    def validate_list(self, input_manager):
        results = []
        for input_token in input_manager:
            code = self.validate_input(input_token)
            results.append((input_token[0], code))
        return results

    def validate_input(self, input):
        code = self.validate_hdf5(input[0])
        if code: return code
        return 0
        #code = self.validate_bw(input[0])
        #if code: return code
        #code = self.validate_hdf5(input[2])
        #if code: return code+1
        #code = self.validate_hdf5(input[3])
        #if code: return code+3
        #return 0

    def validate_bw(self, bw_path):
        if not self.exists(bw_path):
            return 1
        return 0

    def validate_hdf5(self, hdf5_path):
        if not self.exists(hdf5_path):
            return 1
        if not self.is_valid(hdf5_path):
            return 2
        return 0

    def exists(self, file_path):
        return os.path.isfile(file_path)

    def is_valid(self, hdf5_path):
        return h5py.is_hdf5(hdf5_path)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('-l', '--list')
    parser.add_argument('hdf5', nargs='+')
    args = parser.parse_args()

    if args.list:
        input_path = args.list
        hdf5s = InputManager(open(input_path, 'r'))
    else:
        hdf5s = args.hdf5

    results = Validator().validate_list(hdf5s)
    for result in results:
        print "{0}\t{1}".format(result[0], result[1])



if __name__ == '__main__':
    main()
