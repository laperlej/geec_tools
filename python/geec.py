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


def process_unit(args):
    """
    """
    raw_file, name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude = args
    to_hdf5(raw_file, name, chrom_sizes, user_hdf5, resolution)
    filter_hdf5(name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude)


def make_args(list_file, assembly, resolution):
    include = config.REGION[assembly]["all"]
    exclude = config.REGION[assembly]["blacklisted"]
    chrom_sizes = config.CHROM_SIZE[assembly]

    args_list=[]
    for line in list_file:
        line = line.split()
        raw_file = line[0]
        name = line[1]
        user_hdf5 = line[2]
        filtered_hdf5 = line[3]
        args = (raw_file, name, chrom_sizes,
                user_hdf5, filtered_hdf5, resolution,
                include, exclude)
        args_list.append(args)
    return args_list

def main():
    """
    """
    list_path = sys.argv[1]
    assembly = sys.argv[2]
    resolution = sys.argv[3]

    args_list = make_args(open(list_path), assembly, resolution)
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    try:
        pool.map(process_unit, args_list)
    except KeyboardInterrupt:
        pool.terminate()
        exit(1)


if __name__ == '__main__':
    main()
