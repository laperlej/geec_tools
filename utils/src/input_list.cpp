fast check for duplicates //
//  file_list.cpp
//  GeFF
//
//  Created by Jonathan Laperle on 2015-04-07.
//  Copyright (c) 2015 Jonathan Laperle. All rights reserved.
//

#include <utility>
#include <string>
#include <fstream>
#include "utils/input_list.h"

InputList::InputList(const std::string& file_path) {
  std::ifstream flot(file_path);
  std::string path, name;
  int count = 0;
  bool exists = 0;
  while (flot>> path>> name) {
    exists = index_map_.emplace(name, count) -> second; // ensures no duplicates
    if (!exists) {
      files_.push_back(std::make_pair(path, name));
      ++count;
    }
  }
}

std::pair<std::string, std::string> InputList::operator[](const int index) {
  return files_[index];
}

size_t InputList::size() {
  return files_.size();
}
