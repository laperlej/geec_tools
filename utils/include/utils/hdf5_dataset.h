//
//  hdf5_dataset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_HDF5_DATASET_H_
#define UTILS_INCLUDE_UTILS_HDF5_DATASET_H_

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <utility>
#include <boost/dynamic_bitset.hpp>
#include "utils/genomic_data_line.h"
#include "utils/genomic_data_line.h"

class Hdf5Dataset {
 public:
  Hdf5Dataset(const std::string& name, int size, int bin);
  Hdf5Dataset(const std::string& name,
              const std::vector<float>& content,
              int bin);
  Hdf5Dataset(const std::string& name,
              const std::vector<float>& content,
              int bin, float sumX, float sumXX);
  ~Hdf5Dataset() {}
  void FeedDataLine(const GenomicDataLine& token);
  std::string name() {return name_;}
  unsigned int size() {return size_;}
  float sumX() {return sumX_;}
  float sumXX() {return sumXX_;}
  void NormaliseContent();
  void ToZScore();
  void filter(const boost::dynamic_bitset<>& filter) {
    assert(filter.size() == size_);
    std::vector<float> new_content;
    float new_sumX = 0;
    float new_sumXX = 0;
    for (unsigned int i = 0; i < size_; ++i) {
      if (filter[i]){
        new_content.push_back(content_[i]);
        new_sumX += content_[i];
        new_sumXX += content_[i] * content_[i];
      }
    }
    content_ = new_content;
    size_ = new_content.size();
    std::cout << size_<< std::endl;
    sumX_ = new_sumX;
    sumXX_ = new_sumXX;
  }
  std::vector<float>& GetContent();
  float GetPearson(Hdf5Dataset& hdf5_dataset);
  void print() const;
 private:
  std::string name_;
  unsigned int size_;
  int bin_;
  std::vector<float> content_;
  float sumX_;
  float sumXX_;
};

std::vector<float>& zscore(std::vector<float> &v);
std::string to_string(const std::vector<float> &v);

#endif  // UTILS_INCLUDE_UTILS_HDF5_DATASET_H_
