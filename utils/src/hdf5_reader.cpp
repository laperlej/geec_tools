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
#include "utils/genomic_dataset.h"
#include "hdf5_hl.h"

Hdf5Reader::Hdf5Reader(const std::string& file_path) {
  file_path_ = file_path;
  file_id_ = Open();
}

Hdf5Dataset* Hdf5Reader::GetDataset(std::string& name, int bin) {
  // get dimensions
  hsize_t dims;
  H5T_class_t class_id;
  size_t type_size;
  H5LTget_dataset_info(file_id_, name.c_str(), &dims, &class_id, &type_size);
  // get data
  std::vector<float> data;
  data.resize(dims);
  H5LTread_dataset_float(file_id_, name.c_str(), &data[0]);
  Hdf5Dataset* hdf5_dataset = new Hdf5Dataset(name, data, bin, GetSumX(name), GetSumXX(name));
  return hdf5_dataset;
}

GenomicDataset Hdf5Reader::GetGenomicDataset(std::string& name, std::vector<std::string> chroms, int bin) {
  GenomicDataset data = GenomicDataset(name);
  for (std::string chrom : chroms) {
    std::string path = name + "/" + chrom;
    Hdf5Dataset* dataset = GetDataset(path, bin);
    data.add_chromosome(chrom, *dataset);

  }
  return data;
}

float Hdf5Reader::GetSumX(const std::string& name) {
  float sumX;
  std::string attr_name = "sumX";
  H5LTget_attribute_float(file_id_, name.c_str(), attr_name.c_str(), &sumX);
  return sumX;
}

float Hdf5Reader::GetSumXX(const std::string& name) {
  float sumXX;
  std::string attr_name = "sumXX";
  H5LTget_attribute_float(file_id_, name.c_str(), attr_name.c_str(), &sumXX);
  return sumXX;
}

std::string Hdf5Reader::GetHash() {
  std::string hash;
  hash.resize(32);
  std::string attr_name = "hash";
  H5LTget_attribute_string(file_id_, name.c_str(), attr_name.c_str(), &hash[0];
  return hash;
}

bool Hdf5Reader::IsValid(const std::string& path) {
  return H5LTpath_valid(file_id_, path.c_str(), false);
}

hid_t Hdf5Reader::Open() {
  hid_t file_id;
  if (!H5Fis_hdf5(file_path_.c_str())) {   
       // Invalid HDF5 file
       throw std::runtime_error("Failed to open file "+ file_path_);
  }
  file_id = H5Fopen(file_path_.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
  return file_id;
}

void Hdf5Reader::Close() {
  H5Fclose(file_id_);
}
