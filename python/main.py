"""
workflow:
    parse json -> path, md5, assembly
    validation:
        case 1: valid
        case 2: invalid
        case 3: large index
    if large index:
        bwbgbw
        add to valid
    for valid in each assembly:
        to_hdf5
        to_zscore
        correlate
        make_matrix
        heatmap
"""
import sys
import os
import config
from multiprocessing import Pool
import kent
import utils
from bigwig import BigWig


#TODO fix parralel version
#new file name needs to be transfered back to original
"""
def repair_file(dataset):
    if dataset.has_large_index():
        dataset.bwbgbw()

def repair_files_parallel(json):
    try:
        pool = Pool(NUM_THREADS)
        pool.map(repair_file, json.datasets.itervalues())
    finally:
        pool.close()
        pool.join()
"""
def repair_files(datasets):
    for dataset in datasets:
        if dataset.has_large_index():
            dataset.bwbgbw()

def write_output_list(datasets, path):
    with open(path, 'w') as output_list:
        for dataset in datasets.itervalues():
            if dataset.isValid():
                line = '{0}\t{1}\n'.format(dataset.path, dataset.md5sum)
                output_list.write(line)

def load_datasets(input_list):
    datasets = {}
    with open(input_list, 'r') as input_file:
        for line in input_file:
            if line:
                path, md5 = line.split()
                datasets[md5] = path
    return datasets

def main():
    datasets = load_datasets(INPUT_LIST)
    #repair large index files
    repair_files(datasets)
    #prepare to_hdf5 input
    write_output_list(datasets, OUTPUT_LIST)


if __name__ == '__main__':
    INPUT_LIST = sys.argv[1]
    OUTPUT_LIST = sys.argv[2]
    #NUM_THREADS = int(sys.argv[3])
    main()
