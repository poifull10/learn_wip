#pragma once

#include <opencv2/opencv.hpp>

#include <array>
#include <memory>
#include <utility>
#include <vector>

namespace wip
{
class FeatureExtractor
{
public:
  FeatureExtractor(int FASTThresh) : FASTThresh_(FASTThresh) {}

  std::pair<std::vector<cv::KeyPoint>, cv::Mat> operator()(
    const cv::Mat &image) const;

private:
  int FASTThresh_;
};
} // namespace wip
