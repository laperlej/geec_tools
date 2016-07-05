//
//  to_zscore.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

/* this executable is used to generate the data for an nxn correlation matrix
as well as an mxn matrix where filenames1.txt contains "n" and filenames2.txt
contains "m"

Params:
  input.hdf5: an hdf5 file obtained from the to_hdf5 executable
  file_list.txt: input file which contains filenames, one per row
  output.results: output file path
  output.hdf5: output file path
  bin_size: basepair resolution of the hdf5
  include.bed: a bed file with regions to be included
  exclude.bed: a bed file with regions to be excluded

Output:
  a file where every line is "name1vsname2 chrX,0.12313 chrY,0.12313"

note: "filename" is really just the name of the groups as written in the hdf5 file,
they are not nessessarily actual files
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "utils/genomic_file_reader_factory.h"
#include "utils/hdf5_dataset_factory.h"
#include "utils/hdf5_writer.h"
#include "utils/hdf5_reader.h"
#include "utils/input_list.h"
#include "utils/bed_reader.h"
#include "utils/genomic_dataset.h"

int main(int argc, const char * argv[]) {
  std::string input_path, chrom_path, hdf5_path,
              output_path, include_path, exclude_path;
  int bin;

  if (argc < 8) {
    printf("Usage: to_zscore {input.hdf5} "
                         "{output.hdf5} "
                         "{chrom_sizes} "
                         "{bin_size} "
                         "{include.bed} "
                         "{exclude.bed}\n");
    return 1;
  }

  input_path = argv[1];
  output_path = argv[2];
  chrom_path = argv[3];
  bin = std::stoi(argv[4], NULL, 10);
  include_path = argv[5];
  exclude_path = argv[6];

  Hdf5Reader hdf5_reader(input_path);
  Hdf5Writer hdf5_writer(output_path);
  ChromSize chrom_size = ChromSize(chrom_path);

  std::vector<std::string> chroms = chrom_size.get_chrom_list();
  GenomicFileReader* include_reader = GenomicFileReaderFactory::createGenomicFileReader(include_path, "bd", chrom_size)
  GenomicFileReader* exclude_reader = GenomicFileReaderFactory::createGenomicFileReader(exclude_path, "bd", chrom_size)
  FilterBitset include_filter = filter_bitset::FilterBitset(chrom_size, bin, include_reader&)
  FilterBitset exclude_filter = filter_bitset::FilterBitset(chrom_size, bin, exclude_reader&)
  FilterBitset filter = include_filter & !exclude_filter
  
  GenomicDataset genomic_dataset = hdf5_reader.GetGenomicDataset(, chrom_size ,bin)
  genomic_dataset.filter(filter);
  hdf5_writer.AddGenomicDataset(genomic_dataset);
}

/*
std::map<std::string, Hdf5Dataset> get_genomic_dataset(
    const std::string& file_path, ChromSize& chrom_size,
    std::vector<std::string>& chroms, int bin) {

  std::map<std::string, Hdf5Dataset> dataset;
  GenomicFileReader * file_reader =
    GenomicFileReaderFactory::createGenomicFileReader(file_path,
                                                      "bd",
                                                      chrom_size);
  for (std::string chrom : chroms) {
    Hdf5Dataset* chromosome = Hdf5DatasetFactory::createHdf5Dataset(
      file_path, file_reader, chrom, chrom_size[chrom], bin);
    dataset.emplace(chrom, *chromosome);
  }
  return dataset;
}

int main(int argc, const char * argv[]) {
  std::string list_path, chrom_path, hdf5_path,
              output_path, include_path, exclude_path;
  int bin;

  if (argc < 8) {
    printf("Usage: to_zscore {input_list.txt} "
                         "{chrom_sizes} "
                         "{input.hdf5} "
                         "{output.hdf5} "
                         "{bin_size} "
                         "{include.bed} "
                         "{exclude.bed}\n");
    return 1;
  }

  list_path = argv[1];
  chrom_path = argv[2];
  hdf5_path = argv[3];
  output_path = argv[4];
  bin = std::stoi(argv[5], NULL, 10);
  include_path = argv[6];
  exclude_path = argv[7];

  Hdf5Reader hdf5_reader(hdf5_path);
  Hdf5Writer hdf5_writer(output_path);
  InputList input_list(list_path);
  ChromSize chrom_size = ChromSize(chrom_path);

  Hdf5Dataset* hdf5_dataset;

  std::vector<std::string> chroms = chrom_size.get_chrom_list();

  std::map<std::string, Hdf5Dataset> include = get_genomic_dataset(
    include_path, chrom_size, chroms, bin);
  std::map<std::string, Hdf5Dataset> exclude = get_genomic_dataset(
    exclude_path, chrom_size, chroms, bin);

  Hdf5Dataset* include_chrom;
  Hdf5Dataset* exclude_chrom;
  std::string name;

  for (uint64_t i = 0; i < input_list.size(); ++i) {
    for (std::string chrom : chroms) {
      name = input_list[i].second + "/" + chrom;
      if (hdf5_reader.IsValid(name)) {
        hdf5_dataset = hdf5_reader.GetDataset(name, bin);
        include_chrom = &include.at(chrom);
        exclude_chrom = &exclude.at(chrom);
        hdf5_dataset -> filter(*include_chrom, *exclude_chrom);
        hdf5_dataset -> ToZScore();
        hdf5_writer.AddDataset(*hdf5_dataset);
        delete hdf5_dataset;
      }
    }
  }

  return 0;
}
*/