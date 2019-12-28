#pragma once

#include <opencv2/opencv.hpp>

#include "Point.h"
#include "Pose.h"

#include <utility>
#include <vector>

namespace wip
{
class PoseEstimator
{
public:
  virtual std::pair<float, cv::Mat> estimate() const = 0;
  virtual cv::Mat calculate(
    const std::vector<cv::Point2f> &srcPoints,
    const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                         const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual Pose getPose(const cv::Mat &H) const = 0;
};
} // namespace wip
