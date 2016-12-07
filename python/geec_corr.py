import sys
import subprocess
import tempfile
import itertools
import os
from utils import config
from utils.geec_tools import *
import multiprocessing


def create_input_list(input_list):
    file_path = tmp_name()
    with open(file_path, 'w') as input_file:
        for path, label in input_list:
            input_file.write('{0}\t{1}\n'.format(path.strip(),label.strip()))
    return file_path


def tmp_name():
    fd, temp_path = tempfile.mkstemp()
    os.close(fd)
    os.remove(temp_path)
    return temp_path


def main():

    list_path = sys.argv[1]
    corr_path = sys.argv[2]
    mat_path = sys.argv[3]
    assembly = sys.argv[4]
    resolution = sys.argv[5]

    include = config.get_region(assembly,"all")
    exclude = config.get_region(assembly,"blklst")
    chrom_sizes = config.get_chrom_sizes(assembly)

    input_list = []
    with open(list_path, 'r') as list_file:
        for line in list_file:
            line = line.split()
            input_list.append((line[3], line[1]))

    input_path = create_input_list(input_list)

    correlate(input_path, chrom_sizes, corr_path, resolution)
    make_matrix(input_path, chrom_sizes, corr_path, mat_path)

if __name__ == '__main__':
    main()