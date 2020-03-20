#include <Pose.h>
#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>

TEST(Pose, contructor) {
  wip::Pose p;
  EXPECT_DOUBLE_EQ(0, p.x());
  EXPECT_DOUBLE_EQ(0, p.y());
  EXPECT_DOUBLE_EQ(0, p.z());
  EXPECT_DOUBLE_EQ(0, p.rx());
  EXPECT_DOUBLE_EQ(0, p.ry());
  EXPECT_DOUBLE_EQ(0, p.rz());
  EXPECT_DOUBLE_EQ(1, p.rw());

  cv::Mat mat = cv::Mat::eye(3, 3, CV_64F);
  mat.at<double>(cv::Point(0, 0)) = 0.0743002;
  mat.at<double>(cv::Point(1, 0)) = -0.4683898;
  mat.at<double>(cv::Point(2, 0)) = 0.8803923;
  mat.at<double>(cv::Point(0, 1)) = 0.9130010;
  mat.at<double>(cv::Point(1, 1)) = -0.3231657;
  mat.at<double>(cv::Point(2, 1)) = -0.2489841;
  mat.at<double>(cv::Point(0, 2)) = 0.4011342;
  mat.at<double>(cv::Point(1, 2)) = 0.8222985;
  mat.at<double>(cv::Point(2, 2)) = 0.4036291;

  cv::Mat t(3, 1, CV_64F);
  t.at<double>(cv::Point(0, 0)) = 11.123981;
  t.at<double>(cv::Point(0, 1)) = -40.334456;
  t.at<double>(cv::Point(0, 2)) = -900.312122;

  p = wip::Pose(mat, t);
  EXPECT_NEAR(11.123981, p.x(), 1e-4);
  EXPECT_NEAR(-40.334456, p.y(), 1e-4);
  EXPECT_NEAR(-900.312122, p.z(), 1e-4);
  EXPECT_NEAR(0.4984568, p.rx(), 1e-4);
  EXPECT_NEAR(0.2229938, p.ry(), 1e-4);
  EXPECT_NEAR(0.642747, p.rz(), 1e-4);
  EXPECT_NEAR(0.5372996, p.rw(), 1e-4);
}
