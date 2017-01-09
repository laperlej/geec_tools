//
//  to_hdf5.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

/* this executable is used to generate the data for an nxn correlation matrix
as well as an mxn matrix where filenames1.txt contains "n" and filenames2.txt
contains "m"

Params:
  file_list.txt: list of files
  name_list.txt: list of names, must be in same order as file_list
                 those names will be used as hdf5_groups and will
                 have to be provided to other executables which access hdf5 files
  output.hdf5: output file path
  bin_size: basepair resolution of the hdf5

Output:
  a file where every line is "name1:name2 chrX,0.12313 chrY,0.12313"
*/
/*
#if defined(_OPENMP)
  #include <omp.h>
#endif
*/
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/hdf5_writer.h"
#include "utils/input_list.h"
#include "utils/utils.h"


int main(int argc, const char * argv[]) {
  std::string output_path, chrom_path, list_path, input_path, input_name;
  int bin;
  if (argc < 5) {
    printf("Usage: to_hdf5 {dataset.bw} "
                          "{name} "
                          "{chrom_sizes} "
                          "{output.hdf5} "
                          "{bin_size}\n");
    return 1;
  }
  input_path = argv[1];
  input_name = argv[2];
  chrom_path = argv[3];
  output_path = argv[4];
  bin = std::stoi(argv[5], NULL, 10);

  ChromSize chrom_size = ChromSize(chrom_path);
  Hdf5Writer hdf5_writer(output_path);
  //for dymanic type finding: boost::filesystem::extension(input_path)
  GenomicFileReader* genomic_file_reader = GenomicFileReaderFactory::createGenomicFileReader(
          input_path, ".bg", chrom_size);
  Hdf5Dataset* hdf5_dataset = NULL;
  std::vector<std::string> chroms = chrom_size.get_chrom_list();

  for (std::string chrom : chroms) {
    genomic_file_reader->SeekChr(chrom);
    hdf5_dataset = Hdf5DatasetFactory::createHdf5Dataset(
      input_name, genomic_file_reader, chrom, chrom_size[chrom], bin);
    hdf5_dataset -> NormaliseContent();
    hdf5_writer.AddDataset(*hdf5_dataset);
    hdf5_writer.SetHash("/", input_name);
    hdf5_writer.SetChromSizesHash("/", md5sum(chrom_path));
    hdf5_writer.SetBin("/", bin);
    delete hdf5_dataset;
    hdf5_dataset = NULL;
  }
  return 0;
}