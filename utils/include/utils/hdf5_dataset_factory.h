//
//  hdf5_dataset_factory.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_HDF5_DATASET_FACTORY_H_
#define UTILS_INCLUDE_UTILS_HDF5_DATASET_FACTORY_H_

#include <string>
#include <vector>
#include "utils/hdf5_dataset.h"
#include "utils/genomic_file_reader.h"

class Hdf5DatasetFactory {
 public:
  static Hdf5Dataset* createHdf5Dataset(
    const std::string& file_path,
    GenomicFileReader* genomic_file_reader,
    const std::string& chrom,
    int size,
    int bin);
  static Hdf5Dataset* createHdf5Dataset(
    const std::string& name,
    const std::vector<float>& content,
    const std::string& chrom,
    int bin);
};

void FillDataset(GenomicFileReader* genomic_file_reader,
                 Hdf5Dataset* hdf5_dataset,
                 const std::string& chroms);

std::string ExtractName(const std::string& name);

std::string StripLastDot(const std::string& name);

std::string StripLastSlash(const std::string& name);

#endif  // UTILS_INCLUDE_UTILS_HDF5_DATASET_FACTORY_H_
