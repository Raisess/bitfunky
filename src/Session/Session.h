#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace AG {

template <typename Download>
class Session {
public:
  Session() {}
  ~Session() {}

  virtual void push(const std::shared_ptr<Download>&) = 0;
  virtual void push(const std::vector<std::shared_ptr<Download>>&) = 0;
  virtual int handle(const std::function<void(void)>& callback) = 0;

protected:
  std::vector<std::shared_ptr<Download>> queue;
};

}
