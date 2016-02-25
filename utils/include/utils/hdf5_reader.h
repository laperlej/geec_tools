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
#include <string>

class Hdf5Reader {
 public:
  explicit Hdf5Reader(const std::string& file_path);
  ~Hdf5Reader() {Close();}
  Hdf5Dataset* GetDataset(const std::string& name, int bin);
  bool IsValid(const std::string& path);
 private:
  hid_t Open();
  void Close();
  std::string file_path_;
  hid_t file_id_;
};

#endif  // UTILS_INCLUDE_UTILS_HDF5_READER_H_
