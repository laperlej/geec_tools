#include <openssl/md5.h>
#include <string>
#include <iostream>

std::string md5sum(std::string file_path) {
  std::ifstream file(file_path);
  std::basic_string<unsigned char> digest;
  digest.reserve(16);
  std::basic_string<unsigned char> content((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
  MD5(&content[0], content.size(), &digest[0]);
  std::string md5;
  md5.reserve(32);
  for(int i = 0; i < 16; ++i)
    sprintf(&md5[i*2], "%02x", (unsigned int)digest[i]);
  return md5;
}