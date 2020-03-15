#pragma once

#include <utility>

#include "PoseEstimator.h"

namespace wip {
class FundamentalMatrixEstimator : public PoseEstimator {
public:
  FundamentalMatrixEstimator(size_t ransacN = 30) : PoseEstimator(ransacN) {}

  cv::Mat calculate(const std::vector<cv::Point2d> &srcPoints,
                    const std::vector<cv::Point2d> &dstPoints) const override;

  std::tuple<double, std::vector<std::pair<cv::Point2d, cv::Point2d>>>
  evaluate(const cv::Mat &F, std::vector<cv::Point2d> &srcPoints,
           const std::vector<cv::Point2d> &dstPoints) override;

  Pose calcPose(const cv::Mat &H, const cv::Mat &K) override;

private:
  double evalFunc(const double val) const;
};
} // namespace wip
