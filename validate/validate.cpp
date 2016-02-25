//
//  validate.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

/* tries to read a bigwig file

Params:
  file_list.txt: list of bigwig files to validate
*/

#if defined(_OPENMP)
  #include <omp.h>
#endif
#include <vector>
#include <string>
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/input_list.h"

void read_bigwig(GenomicFileReader* genomic_file_reader,
                 ChromSize& chrom_size,
                 std::vector<std::string>& chroms) {
  Hdf5Dataset* hdf5_dataset = NULL;
  for (std::string chrom : chroms) {
      genomic_file_reader->SeekChr(chrom);
      hdf5_dataset = Hdf5DatasetFactory::createHdf5Dataset(
        "test", genomic_file_reader, chrom, chrom_size[chrom], 10000);
      delete hdf5_dataset;
      hdf5_dataset = NULL;
  }
}

int main(int argc, const char * argv[]) {
  std::string list_path, chrom_path, input_path;

  if (argc < 2) {
    printf("Usage: validate {input_list.txt} {chrom_sizes}\n");
    return 1;
  }
  list_path = argv[1];

  InputList input_list(list_path);
  ChromSize chrom_size = ChromSize(chrom_path);
  GenomicFileReader* genomic_file_reader = NULL;

  std::vector<std::string> chroms= chrom_size.get_chrom_list();

  #pragma omp parallel for private(genomic_file_reader, input_path)
  for (int i = 0; i < input_list.size(); ++i) {
    input_path = input_list[i].first;
    #pragma omp critical (stdout)
    {
      printf("Reading: %s\n", input_path.c_str());
    }
    try {
      genomic_file_reader = GenomicFileReaderFactory::createGenomicFileReader(
      input_path, "bw", chrom_size);
      read_bigwig(genomic_file_reader, chrom_size, chroms);
    } catch (std::exception& e) {
      #pragma omp critical (stdout) 
      {
        printf("Error while reading: %s\n", input_path.c_str());
        printf("%s\n", e.what());
      }
    }
    delete genomic_file_reader;
    genomic_file_reader=NULL;
  }
  return 0;
}
