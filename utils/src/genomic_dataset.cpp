//
//  genomic_dataset.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>
#include "utils/genomic_dataset.h"

GenomicDataset::GenomicDataset(const std::string& file_name) {
  file_name_ = file_name;
}

void GenomicDataset::add_chromosome(const std::string& name,
                                    const Hdf5Dataset& hdf5_dataset) {
  chromosomes_.emplace(name, hdf5_dataset);
}

std::string GenomicDataset::get_name() {
  return file_name_;
}

std::string GenomicDataset::get_sizes() {
  std::string sizes = "";
  for (const std::string& chr : chromosomes_) {
    sizes += chr + ":" + chromosomes_[chr].size();
  }
  return sizes;
}

std::map<std::string, float>  GenomicDataset::Correlate(
    GenomicDataset& genomic_dataset,
    std::vector<std::string>& chromosomes) {
  std::map<std::string, float> results;
  for (const std::string& chr : chromosomes) {
    if (chromosomes_.find(chr) != chromosomes_.end() &&
        genomic_dataset.chromosomes_.find(chr) !=
        genomic_dataset.chromosomes_.end()) {
      float r;
      try{
        r = chromosomes_.at(chr).GetPearson(
        genomic_dataset.chromosomes().at(chr));
      } catch (...) {
        r = 0;
      }
      results.emplace(chr, r);
    } else {
      results.emplace(chr, std::numeric_limits<float>::quiet_NaN());
    }
  }
    return results;
}
