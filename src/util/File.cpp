#include <fstream>
#include "File.h"

BF::File::File(const std::string& path) : path(path) {}

BF::File::~File() {}

std::string BF::File::read() {
  std::string data;

  std::fstream file(this->path, file.in);
  std::string tmp;
  while (std::getline(file, tmp)) {
    data += tmp + "\n";
  }
  file.close();

  return data;
}

void BF::File::write(const std::string& data) {
  std::fstream file(this->path, file.out);
  file << data << std::endl;
  file.close();
}

void BF::File::append(const std::string& data) {
  const auto old_data = this->read();
  this->write(old_data + data);
}
