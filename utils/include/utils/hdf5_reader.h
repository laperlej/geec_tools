//
//  hdf5_reader.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_HDF5_READER_H_
#define UTILS_INCLUDE_UTILS_HDF5_READER_H_

#include "hdf5.h"
#include "hdf5_dataset.h"
#include "genomic_dataset.h"
#include <string>

class Hdf5Reader {
 public:
  explicit Hdf5Reader(const std::string& file_path);
  ~Hdf5Reader() {Close();}
  Hdf5Dataset* GetDataset(std::string& name, int bin);
  GenomicDataset GetGenomicDataset(std::string& name, std::vector<std::string> chroms, int bin);
  float GetSumX(const std::string& name);
  float GetSumXX(const std::string& name);
  bool IsValid(const std::string& path);
 private:
  hid_t Open();
  void Close();
  std::string file_path_;
  hid_t file_id_;
};

#endif  // UTILS_INCLUDE_UTILS_HDF5_READER_H_
