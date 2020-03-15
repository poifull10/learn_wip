#include <FeatureExtractor.h>
#include <FeatureMatcher.h>
#include <Image.h>
#include <gtest/gtest.h>

#include <cmath>
#include <opencv2/opencv.hpp>

TEST(FeatureExtractor, test_extract_orb) {
  const auto src = wip::load_image("../data/0001.png");
  const auto dst = wip::load_image("../data/0002.png");

  wip::FeatureExtractor fe;
  wip::FeatureMatcher fm;

  const auto [srcKpt, srcDsc] = fe(src);
  const auto [dstKpt, dstDsc] = fe(dst);

  auto matched = fm({srcKpt, srcDsc}, {dstKpt, dstDsc});

  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  std::vector<cv::DMatch> matches_;
  dm->match(srcDsc, dstDsc, matches_);

  cv::Mat outImage;
  cv::drawMatches(src.data(), srcKpt, dst.data(), dstKpt, matches_, outImage);
  EXPECT_GT(matched.size(), 0);
  cv::imwrite("test_matched.png", outImage);
}