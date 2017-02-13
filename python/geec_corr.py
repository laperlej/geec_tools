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

def correlation(input_file, corr_path, mat_path):
    assembly = geec_config.ASSEMBLY
    include = config.get_region(assembly, geec_config.INCLUDE)
    exclude = config.get_region(assembly, geec_config.EXCLUDE)
    resolution = geec_config.RESOLUTION
    chrom_sizes = config.get_chrom_sizes(assembly)

    input_path = tmp_name()
    corr_input_file = open(input_path, 'w')
    for line in input_file:
        name = line.strip()
        filtered_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution), geec_config.INCLUDE, geec_config.EXCLUDE)
        filtered_hdf5 = os.path.join(geec_config.FILTERED_FOLDER, filtered_name)
        corr_input_file.write("{0}\t{1}\n".format(filtered_hdf5, name))
    corr_input_file.close()
    
    correlate(input_path, chrom_sizes, corr_path, resolution)
    make_matrix(input_path, corr_path, mat_path)
    
def main():
    list_path = sys.argv[1]
    corr_path = sys.argv[2]
    mat_path = sys.argv[3]
    correlation(open(list_path), corr_path, mat_path)

if __name__ == '__main__':
    main()

