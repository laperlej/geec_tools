import subprocess
import config

def load_config(stream):
    config = {}
    for line in open(stream):
        line = line.strip()
        if line:
            line = line.split('=')
            config[line[0].strip()] = line[1].strip()
    return config

def to_hdf5(raw_file, name, chrom_sizes, user_hdf5, resolution):
    """Usage: to_hdf5 {dataset.bw}
                      {name}
                      {chrom_sizes}
                      {output.hdf5}
                      {bin_size}\n"""
    #print [config.BW_TO_HDF5, raw_file, name, chrom_sizes, user_hdf5, resolution]
    subprocess.call([config.BW_TO_HDF5,
                     raw_file,
                     name,
                     chrom_sizes,
                     user_hdf5,
                     resolution])


def filter_hdf5(name, chrom_sizes, user_hdf5, filtered_hdf5, resolution, include, exclude):
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
                     chrom_sizes,
                     resolution,
                     include,
                     exclude
                    ])


def correlate(input_list, chrom_sizes, correlation_file, resolution):
    """Usage: correlation {input_list}
                          {chrom_sizes}
                          {output.results}
                          {bin_size}\n");"""
    subprocess.call([config.CORRELATION,
                     input_list,
                     chrom_sizes,
                     correlation_file,
                     resolution
                     ])


def make_matrix(input_list, correlation_file, output_matrix):
    """
    python make_matrix.py {list_path} {chrom_size} {corr_path} {output_path}
    """
    subprocess.call(['python', 
                     config.MAKE_MATRIX,
                     input_list,
                     correlation_file,
                     output_matrix
                     ])
