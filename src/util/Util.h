#pragma once

#include <cstdint>
#include <iostream>

namespace BF {

class Util {
public:
  static void Sleep(uint16_t ms);
  static const std::string Env(const std::string&);
};

}
