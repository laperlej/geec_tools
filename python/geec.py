import sys
import subprocess
import tempfile
import itertools
import os
from utils.geec_tools import *
from utils import config
import multiprocessing


def process_unit(args):
    raw_file, name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude = args
    to_hdf5(raw_file, name, chrom_sizes, user_hdf5, resolution)
    filter_hdf5(name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude)


def main():
    resolution = "10000"
    assembly = "hg19"
    include = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.all.bed"
    exclude = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.exclude.bed"
    chrom_sizes = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/chrom_sizes/hg19noY.chrom.sizes"

    list_path = sys.argv[1]
    args_list=[]
    with open(list_path, 'r') as list_file:
        for line in list_file:
            line = line.split()
            raw_file = line[0]
            name = line[1]
            user_hdf5 = line[2]
            filtered_hdf5 = line[3]
            args = (raw_file, name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude)
            args_list.append(args)
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    try:
       pool.map(process_unit, args_list)
    except KeyboardInterrupt:
        pool.terminate()
        exit(1)


if __name__ == '__main__':
    main()
