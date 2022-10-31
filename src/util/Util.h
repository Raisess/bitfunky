#pragma once

#include <cstdint>
#include <functional>

namespace BF {

class Util {
public:
  // Loop handled by interrupt signal
  static void Loop(const std::function<void(void)>& callback, uint16_t interval_ms);
  static void Sleep(uint16_t ms);
};

}
