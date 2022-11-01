#pragma once

#include <iostream>

namespace BF {

class File {
public:
  File(const std::string& path);
  ~File();

  std::string read();
  void write(const std::string& data);
  void append(const std::string& data);

private:
  std::string path;

};

}
