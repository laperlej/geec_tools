//
//  hdf5_dataset.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include <cmath>
#include <numeric>
#include <iostream>
#include <vector>
#include "utils/hdf5_dataset.h"

Hdf5Dataset::Hdf5Dataset(const std::string& name, int size, int bin) {
  name_ = name;
  bin_ = bin;
  //  initialise content vector based on the genome size and bin
  int content_size;
  content_size = (size + bin_- 1) / bin_;  // round up
  content_.resize(content_size);
  size_ = content_size;
}

Hdf5Dataset::Hdf5Dataset(const std::string& name,
                         const std::vector<float>& content,
                         int bin) {
  name_ = name;
  content_ = content;
  size_ = content.size();
  bin_ = bin;
}

void Hdf5Dataset::FeedDataLine(const GenomicDataLine& token) {
  int start_bin, end_bin;
  start_bin = token.start_position() / bin_;
  end_bin = token.end_position() / bin_;
  if (start_bin == end_bin) {
    content_[start_bin] += token.score() *
                           (token.end_position() - token.start_position());
  } else {
    content_[start_bin] += token.score() *
                           (bin_ - token.start_position() % bin_);
    content_[end_bin] += token.score() * (token.end_position() % bin_);
    for (int i = start_bin+1; i < end_bin; ++i) {
      content_[i] += token.score() * bin_;
    }
  }
}

void Hdf5Dataset::NormaliseContent() {
  content_[content_.size()-1] /= (size_ % bin_);
  for (int i = 0; i < content_.size()-1; ++i) {
    content_[i] /= bin_;
  }
}

void Hdf5Dataset::ToZScore() {
  content_ = zscore(content_);
}

void Hdf5Dataset::filter(Hdf5Dataset& include, Hdf5Dataset& exclude) {
  std::vector<float> filtered_array;
  std::vector<float>& include_array = include.GetContent();
  std::vector<float>& exclude_array = exclude.GetContent();
  for (int i = 0; i < content_.size(); ++i) {
    if (include_array[i] && !exclude_array[i]) {
      filtered_array.push_back(content_[i]);
    }
  }
  content_ = filtered_array;
  size_ = filtered_array.size();
}

std::vector<float>& Hdf5Dataset::GetContent() {
  return content_;
}

std::string to_string(const std::vector<float> &v) {
  std::string s = "[";
  for (float d : v) {
    s += std::to_string(d) + ", ";
  }
  s += "]";
  return s;
}

std::vector<float>& zscore(std::vector<float> &v) {
    float stdev = 0;
    float mean = 0;
    size_t n = v.size();
    mean = std::accumulate(v.begin(), v.end(), mean);
    mean = mean / n;
    for (int i = 0; i < n ; ++i) {
        v[i] -= mean;
        stdev += pow(v[i], 2.0);
    }
    stdev /= n;
    stdev = pow(stdev, 0.5);
    if (stdev == 0) {
      for (int i = 0; i < n ; ++i) {
        v[i] = 0;
      }
    } else {
      for (int i = 0; i < n ; ++i) {
        v[i] /= stdev;
      }
    }
    return v;
}

float Hdf5Dataset::GetPearson(const Hdf5Dataset& hdf5_dataset) const {
  return pearson(content_, hdf5_dataset.content_);
}

float pearson(const std::vector<float>& v1, const std::vector<float>& v2) {
  float total = 0;
  for (int i = 0; i < v1.size(); ++i) {
    total += v1[i] * v2[i];
  }
  return total / v1.size();
}

void Hdf5Dataset::print() const {
  for (float i : content_) {
    std::cout<< i<< ", ";
  }
  std::cout<< std::endl;
}
