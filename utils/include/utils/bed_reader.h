//
//  bed_reader.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-07-21.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_BED_READER_H_
#define UTILS_INCLUDE_UTILS_BED_READER_H_

#include <string>
#include "utils/genomic_file_reader.h"

class BedReader: public GenomicFileReader {
/*class used to generate tokens from a bed file
tokens contain chromosome, start, end, score

see the parent class GenomicFileReader for more information

Usage:
BedReader bed_reader = BedReader(file_path, chrom_size)
GenomicDataLine genomic_data_line;
bed_reader.SeekChr("chr1")
while(NextToken(genomic_data_line)){
    //do something with token
}

note: since entries in the bed format do not contain a score
    it is set to 1 for all tokens

IMPORTANT: the bed file MUST be ordered to use SeekChr
*/
 public:
  BedReader(const std::string& file_path, const ChromSize& chrom_size);
  ~BedReader() {}
  void SeekChr(const std::string& chromosome);
  bool NextToken(GenomicDataLine&);

 private:
  void OpenStream();
  std::string chr_;
};

#endif  // UTILS_INCLUDE_UTILS_BED_READER_H_
