"""
"""
import sys
import to_hdf5
import filter_hdf5
import geec_corr

def run_geec():
    to_hdf5.to_hdf5(list_file)
    filter_hdf5.filter_hdf5(list_file)
    geec_corr.correlation(list_file, corr_path, mat_path)

def main():
    input_list = sys.argv[1]
    corr_path = sys.argv[2]
    mat_path = sys.argv[3]


if __name__ == '__main__':
    main()

