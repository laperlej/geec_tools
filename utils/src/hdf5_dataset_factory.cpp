//
//  hdf5_dataset_factory.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "utils/hdf5_dataset_factory.h"

Hdf5Dataset* Hdf5DatasetFactory::createHdf5Dataset(
  const std::string& dataset_name,
  GenomicFileReader* genomic_file_reader,
  const std::string& chrom,
  int size,
  int bin) {
    std::string name = ExtractName(dataset_name);
    name += "/" + chrom;
    Hdf5Dataset* hdf5_dataset = new Hdf5Dataset(name, size, bin);
    FillDataset(genomic_file_reader, hdf5_dataset, chrom);
    return hdf5_dataset;
}

Hdf5Dataset* Hdf5DatasetFactory::createHdf5Dataset(
  const std::string& filename,
  const std::vector<float>& content,
  const std::string& chrom,
  int bin) {
    std::string name = filename;
    name += "/" + chrom;
    Hdf5Dataset* hdf5_dataset = new Hdf5Dataset(name, content, bin);
    return hdf5_dataset;
}


void FillDataset(GenomicFileReader* genomic_file_reader,
                 Hdf5Dataset* hdf5_dataset,
                 const std::string& chrom) {
  GenomicDataLine token;
  genomic_file_reader->SeekChr(chrom);
  while (!genomic_file_reader->NextToken(token)) {
    // std::cout<< token.display()<< std::endl; // DEBUG
    hdf5_dataset->FeedDataLine(token);
  }
}

std::string ExtractName(const std::string& name) {
  std::string processed_name;
  // processed_name = StripLastDot(name);
  processed_name = StripLastSlash(name);
  return processed_name;
}

std::string StripLastDot(const std::string& name) {
  size_t last_dot = name.find_last_of(".");
  if (last_dot == std::string::npos) return name;
  std::string tmp = name.substr(0, last_dot);
  return tmp;
}

std::string StripLastSlash(const std::string& name) {
  size_t last_slash = name.find_last_of("/");
  if (last_slash == std::string::npos) return name;
  std::string tmp = name.substr(last_slash);
  return tmp;
}
