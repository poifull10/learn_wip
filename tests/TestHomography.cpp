#include <gtest/gtest.h>

#include "Homography.h"

#include <iostream>
#include <string>

namespace wip
{
TEST(HomographyEstimator, test_calculate)
{
  wip::HomographyEstimator he;
  std::vector<cv::Point2f> src;
  src.emplace_back(1, 2);
  src.emplace_back(2, 6);
  src.emplace_back(-3, 0.3);
  src.emplace_back(9, -4);
  std::vector<cv::Point2f> dst;
  dst.emplace_back(1.22135867, 0.93899514);
  dst.emplace_back(1.64745532, 1.07120274);
  dst.emplace_back(-189.32242839, -54.92238531);
  dst.emplace_back(1.89840739, 1.11539421);

  const auto H = he.calculate(src, dst);

  EXPECT_NEAR(H.at<double>(cv::Point(0, 0)), 0.89125166, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(1, 0)), 0.62396362, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(2, 0)), 0.24830436, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(0, 1)), 0.46690387, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(1, 1)), 0.36307604, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(2, 1)), 0.64246972, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(0, 2)), 0.3591727, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(1, 2)), 0.29780192, 1e-3);
  EXPECT_NEAR(H.at<double>(cv::Point(2, 2)), 1, 1e-3);
}

TEST(HomographyEstimator, test_evaluate)
{
  wip::HomographyEstimator he;
  std::vector<cv::Point2f> src;
  src.emplace_back(1, 2);
  src.emplace_back(2, 6);
  src.emplace_back(-3, 0.3);
  src.emplace_back(9, -4);
  std::vector<cv::Point2f> dst;
  dst.emplace_back(1.22135867, 0.93899514);
  dst.emplace_back(1.64745532, 1.07120274);
  dst.emplace_back(-189.32242839, -54.92238531);
  dst.emplace_back(1.89840739, 1.11539421);

  const auto H = he.calculate(src, dst);
  std::vector<cv::Point3f> src_;

  // cv::convertPointsToHomogeneous(src, src_);
  // cv::Mat srcMat = cv::Mat(src_).reshape(1, 4);
  // std::cout << srcMat << std::endl;
  // std::cout << srcMat.channels() << std::endl;
}
} // namespace wip
