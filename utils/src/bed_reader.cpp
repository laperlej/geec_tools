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

void BedReader::NextChr() {
  GenomicDataLine token;
  while (!NextToken(token)) {}
  if (!genomic_file_stream_.fail()) {
    chr_ = token.chromosome();
    chrom_pos_.emplace(chr_, cursor_);
  }
}

void BedReader::SeekChr(const std::string& chromosome) {
  if (cursor_ > last_pos_) {
    last_pos_ = cursor_;
  }
  if (chrom_pos_.find(chromosome) == chrom_pos_.end()) {
    genomic_file_stream_.seekg(last_pos_);
    while (chr_ != chromosome && !genomic_file_stream_.fail()) {
      NextChr();
    }
    genomic_file_stream_.seekg(cursor_);
  } else {
    cursor_ = chrom_pos_.find(chromosome)->second;
    chr_ = chromosome;
    genomic_file_stream_.clear();
    genomic_file_stream_.seekg(cursor_);
  }
}

bool BedReader::NextToken(GenomicDataLine& genomic_data_line) {
  std::string chr;
  int start;
  int end;
  float score = 1;
  cursor_ = genomic_file_stream_.tellg();
  genomic_file_stream_>> chr>> start>> end;
  genomic_data_line = GenomicDataLine(chr, start, end, score);
  //std::cout<< genomic_data_line.display()<< std::endl;
  return genomic_file_stream_.fail() || chr != chr_;
}

void BedReader::OpenStream() {
  genomic_file_stream_.open(file_path_.c_str(), std::ios::in);
  cursor_ = genomic_file_stream_.tellg();
  last_pos_ = cursor_;
}
