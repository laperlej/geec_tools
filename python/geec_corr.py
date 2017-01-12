import sys
import subprocess
import tempfile
import itertools
import os
from utils import config
from utils.geec_tools import *
import multiprocessing
import geec_config


def tmp_name():
    fd, temp_path = tempfile.mkstemp()
    os.close(fd)
    os.remove(temp_path)
    return temp_path

def correlation(input_path, corr_path, mat_path):
    include = config.get_region(assembly, geec_config.INCLUDE)
    exclude = config.get_region(assembly, geec_config.EXCLUDE)
    assembly = geec_config.ASSEMBLY
    resolution = geec_config.RESOLUTION
    chrom_sizes = config.get_chrom_sizes(assembly)

    correlate(input_path, chrom_sizes, corr_path, resolution)
    make_matrix(input_path, chrom_sizes, corr_path, mat_path)
    
def main():
    list_path = sys.argv[1]
    corr_path = sys.argv[2]
    mat_path = sys.argv[3]
    correlation(list_path, corr_path, mat_path)

if __name__ == '__main__':
    main()

