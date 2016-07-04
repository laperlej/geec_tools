//
//  genomic_dataset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_
#define UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_

#include <map>
#include <string>
#include <vector>
#include "utils/hdf5_dataset.h"

class GenomicDataset {
 public:
    GenomicDataset() {}
    explicit GenomicDataset(const std::string& file_name);
    ~GenomicDataset() {}
    void add_chromosome(const std::string& name,
                        const Hdf5Dataset& hdf5_dataset);
    std::map<std::string, float> Correlate(
        const GenomicDataset& genomic_dataset,
        const std::vector<std::string>& chromosomes) const;
    std::string get_name();
    void filter(FilterBitset& filter) {
      for (pair<const std::string, Hdf5Dataset> chrom : chromosomes_) {
        Hdf5Dataset.filter(filter[chrom.first]);
      }
    }
 private:
     std::map<std::string, Hdf5Dataset> chromosomes_;
     std::string file_name_;
};

#endif  // UTILS_INCLUDE_UTILS_GENOMIC_DATASET_H_
