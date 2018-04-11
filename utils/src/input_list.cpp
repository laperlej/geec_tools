//
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
  bool success = 0;
  while (flot>> path>> name) {
    success = this->index_map_.emplace(name, count).second; // ensures no duplicates
    if (success) {
      this->files_.push_back(std::make_pair(path, name));
      ++count;
    }
  }
}

std::pair<std::string, std::string> InputList::operator[](const int index) {
  return this->files_[index];
}

size_t InputList::size() {
  return this->files_.size();
}