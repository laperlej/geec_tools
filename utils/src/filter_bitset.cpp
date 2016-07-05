#include "utils/filter_bitset.h"

FilterBitset FilterBitset::operator~() {
  FilterBitset filter;
  for(std::pair<const std::string, boost::dynamic_bitset<>> chrom: content_) {
    filter.content().emplace(chrom.first, ~chrom.second);
  }
  return filter;
}

FilterBitset FilterBitset::operator&(const FilterBitset &b) {
  FilterBitset filter;
  for(std::pair<const std::string, boost::dynamic_bitset<>> chrom: content_) {
    filter.content().emplace(chrom.first, chrom.second & b.at(chrom.first));
  }
  return filter;
}