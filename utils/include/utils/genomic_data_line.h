//
//  genomic_data_line.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_GENOMIC_DATA_LINE_H_
#define UTILS_INCLUDE_UTILS_GENOMIC_DATA_LINE_H_

#include <string>

class GenomicDataLine {
 public:
  GenomicDataLine() {}
  GenomicDataLine(std::string chromosome, int start_position, int end_position,
                  float score) {
    chromosome_ = chromosome;
    start_position_ = start_position;
    end_position_ = end_position;
    score_ = score;
  }
  ~GenomicDataLine() {}
  std::string display();
  std::string chromosome() const {return chromosome_;}
  int start_position() const {return start_position_;}
  int end_position() const {return end_position_;}
  float score() const {return score_;}
 private:
  std::string chromosome_;
  int start_position_;
  int end_position_;
  float score_;
};

#endif  // UTILS_INCLUDE_UTILS_GENOMIC_DATA_LINE_H_
