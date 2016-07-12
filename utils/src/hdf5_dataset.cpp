//
//  hdf5_dataset.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <string>
#include <cmath>
#include <utility>
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

Hdf5Dataset::Hdf5Dataset(const std::string& name,
                         const std::vector<float>& content,
                         int bin,
                         float sumX,
                         float sumXX) {
  name_ = name;
  content_ = content;
  size_ = content.size();
  bin_ = bin;
  sumX_ = sumX;
  sumXX_ = sumXX;
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
  sumX_ = 0;
  sumXX_ = 0;
  int last_index = content_.size()-1;
  for (int i = 0; i < last_index-1; ++i) {
    content_[i] /= bin_;
    sumX_ += content_[i];
    sumXX_ += content_[i] * content_[i];
  }
  content_[last_index] /= (size_ % bin_);
  sumX_ += content_[last_index];
  sumXX_ += content_[last_index] * content_[last_index];
}

void Hdf5Dataset::ToZScore() {
  content_ = zscore(content_);
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
    for (unsigned int i = 0; i < n ; ++i) {
        v[i] -= mean;
        stdev += pow(v[i], 2.0);
    }
    stdev /= n;
    stdev = pow(stdev, 0.5);
    if (stdev == 0) {
      for (unsigned int i = 0; i < n ; ++i) {
        v[i] = 0;
      }
    } else {
      for (unsigned int i = 0; i < n ; ++i) {
        v[i] /= stdev;
      }
    }
    return v;
}

float Hdf5Dataset::GetPearson(Hdf5Dataset& hdf5_dataset) {
  assert(size_ == hdf5_dataset.size());
  float r;
  float sumXY = 0;
  std::vector<float>& v1 = content_;
  std::vector<float>& v2 = hdf5_dataset.GetContent();
  for (unsigned int i = 0; i < size_; ++i) {
    sumXY += v1[i] * v2[i];
  }
  float sumY = hdf5_dataset.sumX();
  float sumYY = hdf5_dataset.sumXX();
  //std::cout << sumX_ << std::endl;
  //std::cout << sumXX_ << std::endl;
  //std::cout << sumY << std::endl;
  //std::cout << sumYY << std::endl;
  //std::cout << sumXY << std::endl;
  //float num = sumXY - sumX_ * sumY;
  //float denum = pow(sumXX_ - pow(sumX_, 2), 0.5) * pow(sumYY - pow(sumY, 2), 0.5);
  //std::cout << num << std::endl;
  float num = sumXY - (sumX * sumY / size_)
  float denum = (sumXX_ - pow(sumX_, 2) / size_) * (sumYY - pow(sumY, 2) / size_)
  std::cout << num << std::endl;
  std::cout << denum << std::endl;

  r = num / pow(denum, 0.5);
  return r;
}

void Hdf5Dataset::print() const {
  for (float i : content_) {
    std::cout<< i<< ", ";
  }
  std::cout<< std::endl;
}
