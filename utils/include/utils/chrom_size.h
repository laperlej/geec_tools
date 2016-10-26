//
//  chrom_size.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_CHROM_SIZE_H_
#define UTILS_INCLUDE_UTILS_CHROM_SIZE_H_

#include <string>
#include <map>
#include <vector>

class ChromSize {
 public:
  ChromSize();
  explicit ChromSize(const std::string&);
  ~ChromSize() {}
  int operator[](const std::string&);
  size_t count(const std::string&) const;
  std::vector<std::string> get_chrom_list() const;
 private:
  std::map<std::string, int> chrom_sizes_;
  std::vector<std::string> chrom_list_;
};

#endif  // UTILS_INCLUDE_UTILS_CHROM_SIZE_H_
