import sys
import argparse
import subprocess
import tempfile
import itertools
import os
import config
import multiprocessing

def to_hdf5(raw_file, name, assembly, user_hdf5, resolution):
    """Usage: to_hdf5 {dataset.bw}
                      {name}
                      {chrom_sizes}
                      {output.hdf5}
                      {bin_size}\n"""
    subprocess.call([config.TO_HDF5,
                     raw_file,
                     name,
                     config.CHROM_SIZE[assembly],
                     user_hdf5,
                     resolution])

def filter_hdf5(name, assembly, user_hdf5, user_zscore, resolution, include, exclude):
    """Usage: filter    {input.hdf5}
                        {name}
                        {output.hdf5}
                        {chrom_sizes}
                        {bin_size}
                        {include.bed}
                        {exclude.bed}\n");"""
    subprocess.call([config.FILTER,
                     user_hdf5,
                     name,
                     filtered_hdf5,
                     config.CHROM_SIZE[assembly],
                     resolution,
                     include,
                     exclude
                    ])

def process_unit(args):
	raw_file, name, assembly, user_hdf5, user_zscore, resolution, include, exclude = args
	to_hdf5(raw_file, name, assembly, user_hdf5, resolution)
	filter_hdf5(name, assembly, user_hdf5, user_zscore, resolution, include, exclude)

def correlate(input_list, assembly, correlation_file, resolution):
    """Usage: correlation {input_list}
                          {chrom_sizes}
                          {output.results}
                          {bin_size}\n");"""
    subprocess.call([config.CORRELATION,
                     input_list,
                     config.CHROM_SIZE[assembly],
                     correlation_file,
                     resolution
                     ])

def make_matrix(input_list, assembly, correlation_file, output_matrix):
    """
    python make_matrix.py {list_path} {chrom_size} {corr_path} {output_path}
    """
    subprocess.call(['python', 
                     config.MAKE_MATRIX,
                     input_list,
                     config.CHROM_SIZE[assembly],
                     correlation_file,
                     output_matrix
                     ])

def create_input_list(input_list):
    file_path = tmp_name()
    with open(file_path, 'w') as input_file:
        for path, label in input_list:
            input_file.write('{0}\t{1}\n'.format(path.strip(),label.strip()))
    return file_path

def parse_md5s(md5s_path):
    md5s = []
    if md5s_path:
        with open(md5s_path) as md5s_file:
            md5s_file.readline()
            for line in md5s_file:
                md5s.append(line)
    return md5s

def tmp_name():
    fd, temp_path = tempfile.mkstemp()
    os.close(fd)
    os.remove(temp_path)
    return temp_path

def main():
	resolution = 10000
	assembly = "hg19"
	include = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.all.bed"
	exclude = "/mnt/parallel_scratch_mp2_wipe_on_august_2016/jacques/laperlej/geec_tools/resource/region/hg19.exclude.bed"

	list_path = sys.argv[1]
	args_list=[]
	with open(list_path, 'r') as list_file:
		for line in list_file:
			line = line.split()
			raw_file = line[0]
			name = line[1]
			user_hdf5 = line[2]
			user_zscore = line[3]
			args = (raw_file, name, assembly, user_hdf5, user_zscore, resolution, include, exclude)
			args_list.append(args)
	pool = multiprocessing.Pool(multiprocessing.cpu_count())
	pool.map(process_unit, args_list)


if __name__ == '__main__':
    main()