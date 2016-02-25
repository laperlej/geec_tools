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
import ihec_json
import os
import config
from multiprocessing import Pool


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
def repair_files(json):
    for dataset in json.datasets.itervalues():
        if dataset.has_large_index():
            dataset.bwbgbw()

def write_input_list(json, path):
    with open(path, 'w') as input_list:
        for dataset in json.datasets.itervalues():
            if dataset.isValid():
                line = '{0}\t{1}\n'.format(dataset.path, dataset.md5sum)
                input_list.write(line)

def main():
    json = ihec_json.IhecJson(INPUT_JSON)
    #repair large index files
    repair_files(json)
    #prepare to_hdf5 input
    write_input_list(json, OUTPUT_LIST)


if __name__ == '__main__':
    INPUT_JSON = sys.argv[1]
    OUTPUT_LIST = sys.argv[2]
    #NUM_THREADS = int(sys.argv[3])
    main()
