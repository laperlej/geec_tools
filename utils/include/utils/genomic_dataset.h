//
//  genomic_dataset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_
#define UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_

#include <iostream>
#include <map>
#include <utility>
#include <string>
#include <vector>
#include "utils/hdf5_dataset.h"
#include "utils/filter_bitset.h"

class GenomicDataset {
 public:
    GenomicDataset() {}
    explicit GenomicDataset(const std::string& file_name);
    ~GenomicDataset() {}
    void add_chromosome(const std::string& name,
                        const Hdf5Dataset& hdf5_dataset);
    std::map<std::string, Hdf5Dataset>& chromosomes() {return chromosomes_;}
    std::map<std::string, float> Correlate(
        GenomicDataset& genomic_dataset,
        std::vector<std::string>& chromosomes);
    float  GenomicDataset::CorrelateAll(
      GenomicDataset& genomic_dataset,
        std::vector<std::string>& chromosomes);
    std::string get_name();
    std::string get_sizes();
    void filter(FilterBitset& filter) {
      for (std::pair<const std::string, Hdf5Dataset>& chrom : chromosomes_) {
        chrom.second.filter(filter[chrom.first]);
      }
    }
 private:
     std::map<std::string, Hdf5Dataset> chromosomes_;
     std::string file_name_;
};

#endif  // UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_
