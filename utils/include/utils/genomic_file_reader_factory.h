//
//  genomic_file_reader_factory.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_FACTORY_H_
#define UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_FACTORY_H_

#include <string>
#include "utils/genomic_file_reader.h"

class GenomicFileReaderFactory {
 public:
  static GenomicFileReader* createGenomicFileReader(
    const std::string& file_path,
    const std::string& file_type,
    const ChromSize& chrom_size);
};

#endif  // UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_FACTORY_H_
