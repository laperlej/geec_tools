//
//  hdf5_dataset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_HDF5_DATASET_H_
#define UTILS_INCLUDE_UTILS_HDF5_DATASET_H_

#include <vector>
#include <string>
#include <utility>
#include "utils/genomic_data_line.h"

class Hdf5Dataset {
 public:
  Hdf5Dataset(const std::string& name, int size, int bin);
  Hdf5Dataset(const std::string& name,
              const std::vector<float>& content,
              int bin);
  ~Hdf5Dataset() {}
  void FeedDataLine(const GenomicDataLine& token);
  std::string name() {return name_;}
  int size() {return size_;}
  std::pair<int, int> NormaliseContent();
  void ToZScore();
  void filter(Hdf5Dataset& include, Hdf5Dataset& exclude);
  std::vector<float>& GetContent();
  float GetPearson(const Hdf5Dataset& hdf5_dataset) const;
  void print() const;
 private:
  std::string name_;
  int size_;
  int bin_;
  std::vector<float> content_;
};

std::vector<float>& zscore(std::vector<float> &v);
std::string to_string(const std::vector<float> &v);

float pearson(const std::vector<float>& v1, const std::vector<float>& v2);

#endif  // UTILS_INCLUDE_UTILS_HDF5_DATASET_H_
