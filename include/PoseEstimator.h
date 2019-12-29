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
  PoseEstimator(size_t ransacN = 30) : ransacN_(ransacN) {}

  std::pair<float, cv::Mat> estimate(
    const std::vector<cv::DMatch> &matches,
    const std::vector<cv::KeyPoint> &srcKeyPoints,
    const std::vector<cv::KeyPoint> &dstKeyPoints) const;

  virtual cv::Mat calculate(
    const std::vector<cv::Point2f> &srcPoints,
    const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                         const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual Pose getPose(const cv::Mat &H) const = 0;

protected:
  size_t ransacN_;
};
} // namespace wip
