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
#include "genomic_file_reader_factory.h"
#include "hdf5_dataset_factory.h"
#include "hdf5_writer.h"
#include "input_list.h"
#include "hdf5.h"


int main(int argc, const char * argv[]) {
  std::string output_path, chrom_path, list_path, input_path, input_name;
  int bin;
  if (argc < 4) {
    printf("Usage: to_hdf5 {dataset.bw} "
                          "{chrom_sizes} "
                          "{bin_size} "
                          "{output.hdf5}\n");
    return 1;
  }

  H5Eset_auto(NULL, NULL, NULL);
  input_path = argv[1];
  chrom_path = argv[2];
  bin = std::stoi(argv[3], NULL, 10);
  output_path = argv[4];
  input_name = boost::filesystem::basename("dataset");

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
    hdf5_writer.SetSignal("/", input_name);
    hdf5_writer.SetChromSizes("/", boost::filesystem::basename(chrom_path));
    hdf5_writer.SetBin("/", bin);
    delete hdf5_dataset;
    hdf5_dataset = NULL;
  }
  return 0;
}