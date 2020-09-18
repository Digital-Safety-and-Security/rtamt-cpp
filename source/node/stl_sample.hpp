#ifndef STL_SAMPLE_H
#define STL_SAMPLE_H

#include <cstdint>

namespace node {

struct Sample {
  uint64_t time{0};
  double   value{0.0};

  Sample() = default;
  Sample(uint64_t time, double value) {
    this->time  = time;
    this->value = value;
  }
};
} // namespace node

#endif /* STL_SAMPLE_H */
