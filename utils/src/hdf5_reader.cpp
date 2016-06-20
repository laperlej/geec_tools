//
//  hdf5_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include "utils/hdf5_reader.h"
#include "hdf5_hl.h"

Hdf5Reader::Hdf5Reader(const std::string& file_path) {
  file_path_ = file_path;
  file_id_ = Open();
}

Hdf5Dataset* Hdf5Reader::GetDataset(const std::string& name, int bin) {
  // get dimensions
  hsize_t dims;
  H5T_class_t class_id;
  size_t type_size;
  H5LTget_dataset_info(file_id_, name.c_str(), &dims, &class_id, &type_size);
  // get data
  std::vector<float> data;
  data.resize(dims);
  H5LTread_dataset_float(file_id_, name.c_str(), &data[0]);
  Hdf5Dataset* hdf5_dataset = new Hdf5Dataset(name, data, bin);
  return hdf5_dataset;
}

int Hdf5Reader::GetSumX(const std::string& name) {
  int sumX;
  std::string attr_name = "sumX";
  H5LTget_attribute_int(file_id_, name.c_str(), attr_name.c_str(), &sumX);
  return sumX;
}

int Hdf5Reader::GetSumXX(const std::string& name) {
  int sumXX;
  std::string attr_name = "sumXX";
  H5LTget_attribute_int(file_id_, name.c_str(), attr_name.c_str(), &sumXX);
  return sumXX;
}

bool Hdf5Reader::IsValid(const std::string& path) {
  return H5LTpath_valid(file_id_, path.c_str(), false);
}

hid_t Hdf5Reader::Open() {
  hid_t file_id;
  file_id = H5Fopen(file_path_.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  return file_id;
}

void Hdf5Reader::Close() {
  H5Fclose(file_id_);
}
