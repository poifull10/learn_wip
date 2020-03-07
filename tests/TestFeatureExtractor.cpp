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

  const auto [src_kps, src_desc] = fe(src);
  const auto [dst_kps, dst_desc] = fe(dst);

  wip::FeatureMatcher fm;
  const auto matches = fm(src_desc, dst_desc);

  for (size_t i = 0; i < matches.size(); i++)
  {
    const auto kp1 = src_kps[matches[i].trainIdx];
    const auto kp2 = dst_kps[matches[i].queryIdx];
    const auto diff = kp1.pt - kp2.pt;
    EXPECT_NEAR(cv::norm(diff), 0, 20);
  }
}