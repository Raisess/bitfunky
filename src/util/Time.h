#pragma once

#include <chrono>
#include <cstdint>
#include <thread>

namespace BF {
namespace Util {

class Time {
public:
  static void Sleep(uint16_t ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
  }
};

}
}
