"""
"""

import sys
import subprocess
import tempfile
import itertools
import os
from utils.geec_tools import *
from utils import config
import multiprocessing
import geec_config

def process_unit(args):
    """
    """
    raw_file, name, chrom_sizes, user_hdf5, resolution = args
    to_hdf5(raw_file, name, chrom_sizes, user_hdf5, resolution)

def make_args(list_file, assembly, resolution):
    chrom_sizes = config.get_chrom_sizes(assembly)

    args_list=[]
    for line in list_file:
        line = line.strip()
        name = line[0]
        raw_file = os.path.join(geec_config.BW_FOLDER, name)
        hdf5_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution) , "all", "none")
        user_hdf5 = os.path.join(geec_config.HDF5_FOLDER, hdf5_name)
        args = (raw_file, name, chrom_sizes,
                user_hdf5, resolution)
        args_list.append(args)
    return args_list

def to_hdf5(list_path):
    assembly = geec_config.ASSEMBLY
    resolution = geec_config.RESOLUTION
    args_list = make_args(open(list_path), assembly, resolution))
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
    to_hdf5(list_path)

if __name__ == '__main__':
    main()

