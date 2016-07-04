//
//  hdf5_writer.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "utils/hdf5_writer.h"
#include "hdf5_hl.h"

Hdf5Writer::Hdf5Writer(const std::string& file_path){
  file_path_ = file_path;
  if (FileExists(file_path)) {
    file_id_ = Open();
  } else {
    file_id_ = Create();
  }
}

void Hdf5Writer::AddDataset(const std::string& name,
                        hsize_t size,
                        const std::vector<float>& data) {
  H5LTmake_dataset_float(file_id_, name.c_str(), 1, &size, &data[0]);
}

void Hdf5Writer::AddDataset(Hdf5Dataset& hdf5_dataset) {
  std::string path;
  hsize_t size;
  std::vector<float> data;

  path = hdf5_dataset.name();
  size = hdf5_dataset.size();
  data = hdf5_dataset.GetContent();

  std::pair<std::string, std::string> split_path;
  split_path = SplitPath(path);
  std::string file_name = split_path.first;
  std::string chr_name = split_path.second;

  if (IsValid(file_name)) {
    if (IsValid(path)) {
      std::cout << "WARNING: "<< path<< " already exists"<< std::endl;
    } else {
      AddDataset("/" + path, size, data);
      SetSumX("/" + path, hdf5_dataset.sumX());
      SetSumXX("/" + path, hdf5_dataset.sumXX());
    }
  } else {
    CreateGroup(file_name);
    AddDataset("/" + path, size, data);
    SetSumX("/" + path, hdf5_dataset.sumX());
    SetSumXX("/" + path, hdf5_dataset.sumXX());
  }
}

void Hdf5Writer::AddGenomicDataset(GenomicDataset& genomic_dataset) {
  for (std::pair<const std::string, Hdf5Dataset> chrom: genomic_dataset) {
    AddDataset(chrom.second)
  }
}

void Hdf5Writer::SetSumX(const std::string name, const float sumX) {
  std::string attr_name = "sumX";
  H5LTset_attribute_float(file_id_, ("/" + name).c_str(), attr_name.c_str(), &sumX, 1);
}

void Hdf5Writer::SetSumXX(const std::string name, const float sumXX) {
  std::string attr_name = "sumXX";
  H5LTset_attribute_float(file_id_, ("/" + name).c_str(), attr_name.c_str(), &sumXX, 1);
}

hid_t Hdf5Writer::Open() {
  hid_t file_id;
  file_id = H5Fopen(file_path_.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
  return file_id;
}

hid_t Hdf5Writer::Create() {
  hid_t file_id;
  file_id = H5Fcreate(file_path_.c_str(),
                      H5F_ACC_TRUNC,
                      H5P_DEFAULT,
                      H5P_DEFAULT);
  return file_id;
}

void Hdf5Writer::Close() {
  H5Fclose(file_id_);
}

void Hdf5Writer::CreateGroup(const std::string& file_name) {
  H5Gcreate1(file_id_, file_name.c_str(), 24);
}

hid_t Hdf5Writer::IsValid(const std::string& path) {
  return H5LTpath_valid (file_id_, path.c_str(), true);
}

bool FileExists(const std::string& file_path) {
  return std::ifstream(file_path.c_str()).good();
}

std::pair<std::string, std::string> SplitPath(std::string& path) {
  size_t last_slash = path.find_last_of("/");
  if (last_slash == std::string::npos) {throw;}
  std::string first = path.substr(0, last_slash);
  std::string second = path.substr(last_slash);
  return make_pair(first, second);
}
