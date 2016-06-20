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

#if defined(_OPENMP)
  #include <omp.h>
#endif
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/hdf5_writer.h"
#include "utils/input_list.h"


int main(int argc, const char * argv[]) {
  std::string output_path, chrom_path, list_path, input_path, input_name;
  int bin;
  if (argc < 5) {
    printf("Usage: to_hdf5 {dataset.bw} "
                          "{chrom_sizes} "
                          "{output.hdf5} "
                          "{bin_size}\n");
    return 1;
  }
  input_path = argv[1];
  chrom_path = argv[2];
  output_path = argv[3];
  bin = std::stoi(argv[4], NULL, 10);

  ChromSize chrom_size = ChromSize(chrom_path);
  Hdf5Writer hdf5_writer(output_path);
  GenomicFileReader* genomic_file_reader = GenomicFileReaderFactory::createGenomicFileReader(
          input_path, "bw", chrom_size);;
  Hdf5Dataset* hdf5_dataset = NULL;
  std::vector<std::string> chroms = chrom_size.get_chrom_list();
  bool is_valid;

  for (std::string chrom : chroms) {
    genomic_file_reader->SeekChr(chrom);
    hdf5_dataset = Hdf5DatasetFactory::createHdf5Dataset(
      input_name, genomic_file_reader, chrom, chrom_size[chrom], bin);
    std::pair<int, int> stats = hdf5_dataset -> NormaliseContent();
    hdf5_writer.AddDataset(*hdf5_dataset);
    hdf5_writer.SetSumX(hdf5_dataset->name, stats.first());
    hdf5_writer.SetSumXX(hdf5_dataset->name, stats.second());
    delete hdf5_dataset;
    hdf5_dataset = NULL;
  }
  return 0;
}
/*
int main(int argc, const char * argv[]) {
  std::string output_path, chrom_path, list_path, input_path, input_name;
  int bin;
  if (argc < 5) {
    printf("Usage: to_hdf5 {input_list.txt} "
                          "{chrom_sizes} "
                          "{output.hdf5} "
                          "{bin_size}\n");
    return 1;
  }
  list_path = argv[1];
  chrom_path = argv[2];
  output_path = argv[3];
  bin = std::stoi(argv[4], NULL, 10);

  InputList input_list(list_path);
  ChromSize chrom_size = ChromSize(chrom_path);
  Hdf5Writer hdf5_writer(output_path);
  GenomicFileReader* genomic_file_reader = NULL;
  Hdf5Dataset* hdf5_dataset = NULL;
  std::vector<std::string> chroms = chrom_size.get_chrom_list();
  bool is_valid;

  #pragma omp parallel for private(hdf5_dataset, genomic_file_reader, input_path, input_name, is_valid)
  for (int i = 0; i < input_list.size(); ++i) {
    input_path = input_list[i].first;
    input_name = input_list[i].second;
    #pragma omp critical (write_hdf5)
    {
      is_valid = hdf5_writer.IsValid("/" + input_name);
    }
    if (!is_valid) {
      try {
        genomic_file_reader = GenomicFileReaderFactory::createGenomicFileReader(
          input_path, "bw", chrom_size);
        for (std::string chrom : chroms) {
            genomic_file_reader->SeekChr(chrom);
            hdf5_dataset = Hdf5DatasetFactory::createHdf5Dataset(
              input_name, genomic_file_reader, chrom, chrom_size[chrom], bin);
            hdf5_dataset -> NormaliseContent();
            #pragma omp critical (write_hdf5)
            {
              hdf5_writer.Append(*hdf5_dataset);
            }
            delete hdf5_dataset;
            hdf5_dataset = NULL;
        }
        delete genomic_file_reader;
        genomic_file_reader = NULL;
      } catch (std::exception& e) {
        #pragma omp critical (stdout) 
        {
          printf("Error while reading: %s\n", input_path.c_str());
          delete hdf5_dataset;
          hdf5_dataset = NULL;
          delete genomic_file_reader;
          genomic_file_reader = NULL;
        }
      }
    }
  }
  return 0;
}
*/