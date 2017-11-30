import sys
import subprocess
import tempfile
import itertools
import os
import utils
from utils import config
from utils.geec_tools import *
import multiprocessing


def tmp_name():
    fd, temp_path = tempfile.mkstemp()
    os.close(fd)
    os.remove(temp_path)
    return temp_path

def correlation_nm(input_file1, input_file2, corr_path, mat_path):
    assembly = geec_config["assembly"]
    include = config.get_region(assembly, geec_config["include"])
    exclude = config.get_region(assembly, geec_config["exclude"])
    resolution = geec_config["resolution"]
    chrom_sizes = config.get_chrom_sizes(assembly)
    precalc = config.get_matrix(assembly, resolution, include, exclude, metric="pearson")
    
    input_paths = []
    for input_file in [input_file1, input_file2]:
        input_path = tmp_name()
        input_paths.append(input_path)
        corr_input_file = open(input_path, 'w')
        for line in input_file:
            name = line.strip()
            filtered_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution), geec_config["include"], geec_config["exclude"])
            filtered_hdf5 = os.path.join(geec_config["filtered_folder"], filtered_name)
            corr_input_file.write("{0}\t{1}\n".format(filtered_hdf5, name))
        corr_input_file.close()
    
    correlate_nm(input_paths[1], input_paths[2], chrom_sizes, corr_path, resolution)
    """
    #concat input path files
    input_path_cat = tmp_name()
    with open(input_path_cat, 'w') as input_file_cat:
        for input_path in input_paths:
            with open(input_path) as input_file:
                for line in input_file:
                    input_file_cat.write(line + '\t')
    
    make_matrix(input_path_cat, corr_path, mat_path)
    """
    make_matrix_nm(input_path[1], input_path[2], corr_path, precalc, mat_path)
    
def main():
    list_path = sys.argv[1]
    list_path2 = sys.argv[2]
    corr_path = geec_config["corr_path"]
    mat_path = geec_config["mat_path"]
    correlation_nm(open(list_path), open(list_path2), corr_path, mat_path)

if __name__ == '__main__':
    geec_config = load_config(sys.argv[3])
    main()

