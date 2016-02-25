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
  while (flot>> path>> name) {
    files_.push_back(path);
    names_.push_back(name);
  }
}

std::pair<std::string, std::string> InputList::operator[](const int index) {
  return std::make_pair(files_[index], names_[index]);
}

size_t InputList::size() {
  return files_.size();
}
