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

  std::vector<std::tuple<cv::KeyPoint, cv::KeyPoint>> operator()(
    const std::tuple<std::vector<cv::KeyPoint>, cv::Mat>& src,
    const std::tuple<std::vector<cv::KeyPoint>, cv::Mat>& dst);

  size_t size() const { return matches_.size(); }

private:
  std::vector<cv::DMatch> matches_;
};
} // namespace wip
