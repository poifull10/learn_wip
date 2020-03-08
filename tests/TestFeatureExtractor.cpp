#include <FeatureExtractor.h>
#include <FeatureMatcher.h>
#include <Image.h>
#include <gtest/gtest.h>

#include <cmath>

TEST(FeatureExtractor, test_extract_orb)
{
  const auto src = wip::load_image("../data/0001.png");
  const auto dst = wip::load_image("../data/0002.png");

  wip::FeatureExtractor fe;
  wip::FeatureMatcher fm;

  const auto matched = fm(fe(src), fe(dst));

  for (const auto& [src_kps, dst_kps] : matched)
  {
    const auto kp1 = src_kps;
    const auto kp2 = dst_kps;
    const auto diff = kp1.pt - kp2.pt;
    EXPECT_NEAR(cv::norm(diff), 0, 20);
  }
}