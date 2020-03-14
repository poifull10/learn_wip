#pragma once

#include <numeric>
#include <utility>
#include <vector>

namespace wip {
class RandomSampler {
public:
  RandomSampler(size_t nMaxSamples)
    : nMaxSamples_(nMaxSamples), labels_(nMaxSamples) {
    std::iota(labels_.begin(), labels_.end(), 0);
  }

  std::vector<size_t> sample(size_t nSamples);

private:
  size_t nMaxSamples_;
  std::vector<size_t> labels_;
};

} // namespace wip