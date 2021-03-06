#include <gtest/gtest.h>

#include "PoseEstimator.h"

TEST(PoseEstimator, test_composite_projection_matrix) {
  cv::Mat K = (cv::Mat_<double>(3, 3) << -1, -2, -3, -4, -5, -6, -7, -8, -9);
  cv::Mat R = (cv::Mat_<double>(3, 3) << 1, 2, 3, 4, 5, 6, 7, 8, 9);
  cv::Mat t = (cv::Mat_<double>(3, 1) << 10, 11, 12);

  const auto P =
    wip::compositeProjectionMatrix(cv::Mat::eye(3, 3, CV_64F), R, t);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(0, 0)), 1);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(1, 0)), 2);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(2, 0)), 3);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(3, 0)), 10);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(0, 1)), 4);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(1, 1)), 5);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(2, 1)), 6);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(3, 1)), 11);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(0, 2)), 7);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(1, 2)), 8);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(2, 2)), 9);
  EXPECT_DOUBLE_EQ(P.at<double>(cv::Point(3, 2)), 12);
}
