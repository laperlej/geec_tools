import sys
import os
import h5py
from utils.utils import InputManager


class Validator(object):
    def validate_list(self, input_manager):
        results = []
        for input_token in input_manager:
            code = self.validate_input(input_token)
            results.append((input_token[0], code))
        return results

    def validate_input(self, input):
        code = self.validate_bw(input[0])
        if code: return code
        code = self.validate_hdf5(input[2])
        if code: return code+1
        code = self.validate_hdf5(input[3])
        if code: return code+3
        return 0

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
    input_path = sys.argv[1]
    input_manager = InputManager(open(input_path, 'r'))
    results = Validator().validate_list(input_manager)
    for result in results:
        print "{0}\t{1}".format(result[0], result[1])



if __name__ == '__main__':
    main()
