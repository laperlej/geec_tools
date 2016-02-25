//
//  genomic_file_reader.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-06.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_H_
#define UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_H_

#include <fstream>
#include <string>
#include "utils/genomic_data_line.h"
#include "utils/chrom_size.h"

class GenomicFileReader {
 public:
  GenomicFileReader(const std::string& file_path, const ChromSize& chrom_size);
  virtual ~GenomicFileReader() {}
  virtual void SeekChr(const std::string& chromosome) = 0;
  virtual bool NextToken(GenomicDataLine&) = 0;
 protected:
  std::string file_path_;
  ChromSize chrom_size_;
  std::ifstream genomic_file_stream_;
};

#endif  // UTILS_INCLUDE_UTILS_GENOMIC_FILE_READER_H_
