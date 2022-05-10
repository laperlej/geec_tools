//
//  bigwig_reader.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_BIGWIG_READER_H_
#define UTILS_INCLUDE_UTILS_BIGWIG_READER_H_

#include <string>
#include "BBFileReader.h"
#include "utils/genomic_file_reader.h"

class BigWigReader: public GenomicFileReader {
 public:
  BigWigReader(const std::string& file_path, const ChromSize& chrom_size);
  ~BigWigReader() {delete bigwig_;}
  void SeekChr(const std::string& chromosome);
  bool NextToken(GenomicDataLine&);
 private:
  BBFileReader* bigwig_;
  BigWigIterator bigwig_it_;
  void OpenStream();
};

#endif  // UTILS_INCLUDE_UTILS_BIGWIG_READER_H_
