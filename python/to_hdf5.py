"""
"""

import sys
import subprocess
import tempfile
import itertools
import os
import utils
import utils.geec_tools as geec
from utils import config
import multiprocessing

def process_unit(args):
    """
    """
    raw_file, name, chrom_sizes, user_hdf5, resolution = args
    geec.to_hdf5(raw_file, name, chrom_sizes, user_hdf5, resolution)

def make_args(list_file, assembly, resolution):
    chrom_sizes = config.get_chrom_sizes(assembly)

    args_list=[]
    for line in list_file:
        name = line.strip()
        raw_file = os.path.join(geec_config["bw_folder"], name)
        hdf5_name = "{0}_{1}_{2}_{3}.hdf5".format(name, config.get_resolution(resolution) , "all", "none")
        user_hdf5 = os.path.join(geec_config["hdf5_folder"], hdf5_name)
        args = (raw_file, name, chrom_sizes,
                user_hdf5, resolution)
        args_list.append(args)
    return args_list

def to_hdf5(list_path):
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
    to_hdf5(list_path)

if __name__ == '__main__':
    geec_config = geec.load_config(sys.argv[2])
    main()

