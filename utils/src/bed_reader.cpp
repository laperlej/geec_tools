//
//  bed_reader.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-07-21.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <iostream>
#include <string>
#include "utils/bed_reader.h"

BedReader::BedReader(const std::string& file_path,
                     const ChromSize& chrom_size):
                     GenomicFileReader(file_path, chrom_size) {
    OpenStream();
};

void BedReader::SeekChr(const std::string& chromosome) {
  /*positions the cursor at a given chromosome

  params:
      chromosome: a string corresponding to a chromosome name 
        as they appear in the file ex:"chr1"

  IMPORTANT: the bed file MUST be ordered to use SeekChr
  */
  std::streampos cursor;
  chr_ = chromosome;
  GenomicDataLine genomic_data_line;
  genomic_file_stream_.seekg(0);
  do {
    cursor = genomic_file_stream_.tellg();
    NextToken(genomic_data_line);
  } while (genomic_data_line.chromosome() != chromosome &&
           !genomic_file_stream_.fail());
  genomic_file_stream_.seekg(cursor);
}

bool BedReader::NextToken(GenomicDataLine& genomic_data_line) {
  /*change genomic_data_line to the next token

  params:
    genomic_data_line: a GenomicDataLine object to be overwriten
  output: bool which indicated if there is more to read
  */
  std::string chr;
  int start;
  int end;
  float score = 1;
  genomic_file_stream_>> chr>> start>> end;
  genomic_data_line = GenomicDataLine(chr, start, end, score);
  return genomic_file_stream_.fail() || chr != chr_;
}

void BedReader::OpenStream() {
  /*opens a stream on the input file, called from constructor
  */
  genomic_file_stream_.open(file_path_.c_str(), std::ios::in);
}
