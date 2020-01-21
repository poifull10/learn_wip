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

  virtual Pose calcPose(const cv::Mat &HorF, const cv::Mat &K) = 0;

  std::pair<cv::Mat, cv::Mat> validatePose(
    const std::vector<cv::Mat> &rotations,
    const std::vector<cv::Mat> &translations, const cv::Mat &K);

protected:
  size_t ransacN_;
  std::vector<std::pair<cv::Point2f, cv::Point2f>> inliners_;
};

cv::Mat compositeProjectionMatrix(const cv::Mat &K, const cv::Mat &R,
                                  const cv::Mat &t);
} // namespace wip
