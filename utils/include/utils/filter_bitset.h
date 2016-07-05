//
//  filter_bitset.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_FILTER_BITSET_H_
#define UTILS_INCLUDE_UTILS_FILTER_BITSET_H_

#include <math.h>
#include <utility>
#include <boost/dynamic_bitset.hpp>
#include "chrom_size.h"
#include "genomic_file_reader.h"

class FilterBitset {
 public:
    FilterBitset();
    FilterBitset(ChromSize& chrom_size, int bin, GenomicFileReader& genomic_file_reader) {
        bin_ = bin;
        std::vector<std::string> chrom_list = chrom_size.get_chrom_list();
        for (std::string& chrom : chrom_list) {
            int size = ceil(chrom_size[chrom] / bin);
            boost::dynamic_bitset<> filter(size);

            GenomicDataLine token;
            genomic_file_reader.SeekChr(chrom);
            while (!genomic_file_reader.NextToken(token)) {
              feed_data_line(filter, token, chrom);
            }

            content_.emplace(chrom, filter);
        }
    };
    ~FilterBitset() {};
    boost::dynamic_bitset<>& operator[](const std::string& chrom){return content_[chrom];}
    void feed_data_line(boost::dynamic_bitset<>& filter, const GenomicDataLine& token, const std::string& chrom) {
      int start_bin, end_bin;
      start_bin = token.start_position() / bin_;
      end_bin = token.end_position() / bin_;
      for (int i = start_bin; i <= end_bin; ++i) {
        content_[chrom][i] = 1;
      }
    }
    FilterBitset operator~() {
      FilterBitset filter;
      for(std::pair<const std::string, boost::dynamic_bitset<>> chrom: content_) {
        filter.content().emplace(chrom.first, ~chrom.second);
      }
      return filter;
    }
    FilterBitset operator&(FilterBitset &b) {
      FilterBitset filter;
      for(std::pair<const std::string, boost::dynamic_bitset<>> chrom: content_) {
        filter.content().emplace(chrom.first, chrom.second & b[chrom.first]);
      }
      return filter;
    }
    unsigned int size() {return content_.size();}
    std::map<std::string, boost::dynamic_bitset<>>& content() {return content_&;}
 private:
    std::map<std::string, boost::dynamic_bitset<>> content_;
    int bin_;
};

#endif  // UTILS_INCLUDE_UTILS_FILTER_BITSET_H_
