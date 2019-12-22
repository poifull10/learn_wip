#include <gtest/gtest.h>

#include "Dataset.h"

#include <filesystem>
#include <iostream>

TEST(Dataset, test_constructor)
{
  std::string fname = "../tests/test_calib.json";
  wip::PinholeCameraModel pcm(fname);
  const auto K = pcm.K();
  EXPECT_FLOAT_EQ(K.at<float>(cv::Point(0, 0)), 100);
  EXPECT_FLOAT_EQ(K.at<float>(cv::Point(2, 0)), 32);
  EXPECT_FLOAT_EQ(K.at<float>(cv::Point(1, 1)), 103);
  EXPECT_FLOAT_EQ(K.at<float>(cv::Point(2, 1)), 16);
}
