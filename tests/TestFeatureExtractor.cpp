#include <gtest/gtest.h>

#include <FeatureExtractor.h>

TEST(FeatureExtractor, test_extract_orb)
{
  const auto src = cv::imread("../tests/lenna.png");
  const auto dst = cv::imread("../tests/lenna_hflip.png");

  wip::FeatureExtractor fe(30);

  const auto [src_kps, src_desc] = fe(src);
  const auto [dst_kps, dst_desc] = fe(dst);

  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(src_desc, dst_desc, matches);

  cv::Mat output;
  cv::drawMatches(src, src_kps, dst, dst_kps, matches, output);

  cv::imwrite("test.png", output);
}