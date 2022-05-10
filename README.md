# GeFF
Genomic Feature Finder

how to use:
mkdir build
cd build
cmake ..
make

copy bigWigInfo to resource/bin
copy bedGraphToBigWig to resource/bin
copy bigWigToBedGraph to resource/bin

# Plan

user input:
    input_list
    chrom_sizes = cannonique - chrY
    bin = 10000
    include = all
    exclude = none

to_hdf5 {input_list.txt} "
          "{chrom_sizes} "
          "{output.hdf5} "
          "{bin_size}\n");

to_zscore {input_list.txt} "
         "{chrom_sizes} "
         "{input.hdf5} "
         "{output.hdf5} "
         "{bin_size} "
         "{include.bed} "
         "{exclude.bed}\n");

corr {input_list} "
     "{chrom_sizes} "
     "{input.hdf5} "
     "{output.results} "
     "{bin_size}\n");

make_matrix.py {list_path} {chrom_size} {corr_path} {output_path}"