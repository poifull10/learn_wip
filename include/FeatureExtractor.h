#pragma once

#include <opencv2/opencv.hpp>

#include <array>
#include <memory>
#include <vector>

namespace wip
{
class FeatureExtractor
{
public:
  FeatureExtractor() = default;

  std::vector<cv::Mat> operator()(const cv::Mat &image) const;
};
} // namespace wip
