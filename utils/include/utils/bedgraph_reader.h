//
//  bedgraph_reader.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_BEDGRAPH_READER_H_
#define UTILS_INCLUDE_UTILS_BEDGRAPH_READER_H_

#include <string>
#include <map>
#include "utils/genomic_file_reader.h"

class BedGraphReader: public GenomicFileReader {
 public:
  BedGraphReader(const std::string& file_path, const ChromSize& chrom_size);
  ~BedGraphReader() {}
  void SeekChr(const std::string& chromosome);
  void NextChr();
  bool NextToken(GenomicDataLine&);
 private:
  int NextChr();
  void OpenStream();
  std::string chr_;
  std::streampos cursor_;
  std::map<std::string, std::streampos> chrom_pos_;
};

#endif  // UTILS_INCLUDE_UTILS_BEDGRAPH_READER_H_
