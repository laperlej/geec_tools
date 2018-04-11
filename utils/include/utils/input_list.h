//
//  file_list.h
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#ifndef UTILS_INCLUDE_UTILS_INPUT_LIST_H_
#define UTILS_INCLUDE_UTILS_INPUT_LIST_H_

#include <map>
#include <utility>
#include <string>
#include <vector>

class InputList {
 public:
  InputList();
  explicit InputList(const std::string& file_path);
  ~InputList() {}
  std::pair<std::string, std::string> operator[](const int index);
  size_t size();
  int get_index(std::string& s){
    return index_map_[s];
  };
 private:
  std::vector<std::pair<std::string, std::string>> files_;
  std::map<std::string, int> index_map_;
};

#endif  // UTILS_INCLUDE_UTILS_INPUT_LIST_H_
