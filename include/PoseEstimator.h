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
  PoseEstimator(size_t ransacN = 30) : ransacN_(ransacN), inliners_() {}

  std::pair<float, cv::Mat> estimate(
    const std::vector<cv::DMatch> &matches,
    const std::vector<cv::KeyPoint> &srcKeyPoints,
    const std::vector<cv::KeyPoint> &dstKeyPoints);

  virtual cv::Mat calculate(
    const std::vector<cv::Point2f> &srcPoints,
    const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual float evaluate(const cv::Mat &HorF,
                         std::vector<cv::Point2f> &srcPoints,
                         const std::vector<cv::Point2f> &dstPoints) = 0;

  virtual Pose calcPose(const cv::Mat &H, const cv::Mat &K,
                        const std::vector<cv::Point2f> &src,
                        const std::vector<cv::Point2f> &dst) const = 0;

protected:
  size_t ransacN_;
  std::vector<std::pair<cv::Point2f, cv::Point2f>> inliners_;
};

cv::Mat compositeProjectionMatrix(const cv::Mat &K, const cv::Mat &R,
                                  const cv::Mat &t);
} // namespace wip
