
#include "RandomSampler.h"

#include <algorithm>
#include <random>

namespace wip {
std::vector<size_t> RandomSampler::sample(size_t nSamples) {
  auto labels = labels_;
  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());
  std::shuffle(labels.begin(), labels.end(), engine);
  return std::vector<size_t>(labels.begin(), labels.begin() + nSamples);
}
} // namespace wip
