#include <gtest/gtest.h>

#include "RandomSampler.h"

TEST(RandomSampler, test_sample)
{
  wip::RandomSampler sampler(10);
  const auto [samples, others] = sampler.sample(3);

  EXPECT_EQ(samples.size(), 3);
  EXPECT_EQ(others.size(), 7);

  std::vector<size_t> actual;
  actual.insert(actual.end(), samples.begin(), samples.end());
  actual.insert(actual.end(), others.begin(), others.end());
  std::sort(actual.begin(), actual.end());

  std::vector<size_t> expected(10);
  std::iota(expected.begin(), expected.end(), 0);

  for (size_t i = 0; i < 10; i++)
  {
    EXPECT_EQ(expected[i], actual[i]);
  }
}
