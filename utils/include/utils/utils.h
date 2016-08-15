#include <openssl/md5.h>
#include <string>
#include <iostream>

std::string md5sum(std::string file_path) {
  std::ifstream file(file_path);
  std::string md5;
  md5.reserve(16);
  std::basic_string<unsigned char> content((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
  md5 = MD5(&content[0], content.size(), &md5[0]);
  return md5
}