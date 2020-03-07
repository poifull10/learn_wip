#pragma once

#include <opencv2/opencv.hpp>
#include <tuple>
#include <vector>

namespace wip
{
class FeatureMatcher
{
public:
  FeatureMatcher() {}

  std::vector<cv::DMatch> operator()(const cv::Mat& srcDesc,
                                     const cv::Mat& dstDesc) const;
};
} // namespace wip
