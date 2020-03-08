#include <gtest/gtest.h>

#include "RandomSampler.h"

TEST(RandomSampler, test_sample)
{
  wip::RandomSampler sampler(10);
  const auto samples = sampler.sample(3);

  EXPECT_EQ(samples.size(), 3);

  auto actual = sampler.sample(10);
  std::sort(actual.begin(), actual.end());

  std::vector<size_t> expected(10);
  std::iota(expected.begin(), expected.end(), 0);

  for (size_t i = 0; i < 10; i++)
  {
    EXPECT_EQ(expected[i], actual[i]);
  }
}
