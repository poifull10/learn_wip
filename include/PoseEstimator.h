#pragma once

#include <opencv2/opencv.hpp>
#include <utility>
#include <vector>

#include "Point.h"
#include "Pose.h"

namespace wip {
class PoseEstimator {
public:
  PoseEstimator(size_t ransacN = 30) : ransacN_(ransacN), inliners_() {}

  std::pair<double, cv::Mat> estimate(
    const std::vector<std::tuple<cv::KeyPoint, cv::KeyPoint>> &keyPoints);

  virtual cv::Mat
  calculate(const std::vector<cv::Point2d> &srcPoints,
            const std::vector<cv::Point2d> &dstPoints) const = 0;

  virtual std::tuple<double, std::vector<std::pair<cv::Point2d, cv::Point2d>>>
  evaluate(const cv::Mat &HorF, const std::vector<cv::Point2d> &srcPoints,
           const std::vector<cv::Point2d> &dstPoints) = 0;

  virtual Pose calcPose(const cv::Mat &HorF, const cv::Mat &K) = 0;

  std::pair<cv::Mat, cv::Mat>
  validatePose(const std::vector<cv::Mat> &rotations,
               const std::vector<cv::Mat> &translations, const cv::Mat &K);

  std::vector<std::pair<cv::Point2d, cv::Point2d>> inliers() const {
    return inliners_;
  }

  std::vector<cv::Point2d> usedSrcPoints() const { return usedSrcPoints_; }
  std::vector<cv::Point2d> usedDstPoints() const { return usedDstPoints_; }

protected:
  size_t ransacN_;
  std::vector<std::pair<cv::Point2d, cv::Point2d>> inliners_;
  std::vector<cv::Point2d> usedSrcPoints_, usedDstPoints_;
};

cv::Mat compositeProjectionMatrix(const cv::Mat &K, const cv::Mat &R,
                                  const cv::Mat &t);
} // namespace wip
