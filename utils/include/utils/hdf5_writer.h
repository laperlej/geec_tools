//
//  hdf5_writer.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_HDF5_WRITER_H_
#define UTILS_INCLUDE_UTILS_HDF5_WRITER_H_

#include <vector>
#include "hdf5.h"
#include "utils/hdf5_dataset.h"
#include "utils/genomic_dataset.h"

class Hdf5Writer {
 public:
  explicit Hdf5Writer(const std::string& file_path);
  ~Hdf5Writer() {Close();}
  void AddDataset(const std::string& name,
              hsize_t size,
              const std::vector<float>& data);
  void AddDataset(Hdf5Dataset& hdf5_dataset);
  void AddGenomicDataset(GenomicDataset& genomic_dataset);
  void SetSumX(const std::string name, float sumX);
  void SetSumXX(const std::string name, float sumXX);
  void SetHash(const std::string name, const std::string hash);
  void SetChromSizesHash(const std::string name, const std::string chrom_sizes_hash);
  void SetBin(const std::string name, const int bin);
  void SetIncludeHash(const std::string name, const std::string include_hash);
  void SetExcludeHash(const std::string name, const std::string exclude_hash);
  htri_t IsValid(const std::string& path);
 private:
  hid_t Open();
  hid_t Create();
  void Close();
  void CreateGroup(const std::string& file_name);
  std::string file_path_;
  hid_t file_id_;
};

bool FileExists(const std::string& file_path);
std::pair<std::string, std::string> SplitPath(std::string& path);

#endif  // UTILS_INCLUDE_UTILS_HDF5_WRITER_H_
