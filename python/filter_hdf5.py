"""
"""

import sys
import subprocess
import tempfile
import itertools
import os
from . import utils
from utils.geec_tools import *
from utils import config
import multiprocessing

def process_unit(args):
    """
    """
    name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude = args
    filter_hdf5(name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude)


def make_args(list_file, assembly, resolution):
    include = config.get_region(assembly, geec_config["include"])
    exclude = config.get_region(assembly, geec_config["exclude"])
    chrom_sizes = config.get_chrom_sizes(assembly)

    args_list=[]
    for line in list_file:
        name = line.strip()
        hdf5_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution) , "all", "none")
        filtered_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution) , geec_config["include"], geec_config["exclude"])
        user_hdf5 = os.path.join(geec_config["hdf5_folder"], hdf5_name)
        filtered_hdf5 = os.path.join(geec_config["filtered_folder"], filtered_name)
        args = (name, chrom_sizes,
                user_hdf5, filtered_hdf5, resolution,
                include, exclude)
        args_list.append(args)
    return args_list

def hdf5_filter(list_path):
    assembly = geec_config["assembly"]
    resolution = geec_config["resolution"]
    args_list = make_args(open(list_path), assembly, resolution)
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    try:
        pool.map(process_unit, args_list)
    except KeyboardInterrupt:
        pool.terminate()
        exit(1)

def main():
    """
    """
    list_path = sys.argv[1]
    hdf5_filter(list_path)

if __name__ == '__main__':
    geec_config = load_config(sys.argv[2])
    main()
