#include <gtest/gtest.h>

#include <iostream>

#include <FeatureExtractor.h>
#include <Image.h>

TEST(FeatureExtractor, test_extract_orb)
{
  const auto src = wip::load_image("../tests/lenna.png");
  const auto dst = wip::load_image("../tests/lenna_90.png");

  wip::FeatureExtractor fe;

  const auto [src_kps, src_desc] = fe(src);
  const auto [dst_kps, dst_desc] = fe(dst);

  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(src_desc, dst_desc, matches);

  cv::Mat output;
  cv::drawMatches(src.data(), src_kps, dst.data(), dst_kps, matches, output);

  cv::imwrite("test.png", output);
}