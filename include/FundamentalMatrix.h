#pragma once

#include <utility>

#include "PoseEstimator.h"

namespace wip {
class FundamentalMatrixEstimator : public PoseEstimator {
public:
  FundamentalMatrixEstimator(size_t ransacN = 30) : PoseEstimator(ransacN) {}

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  std::tuple<float, std::vector<std::pair<cv::Point2f, cv::Point2f>>>
  evaluate(const cv::Mat &F, std::vector<cv::Point2f> &srcPoints,
           const std::vector<cv::Point2f> &dstPoints) override;

  Pose calcPose(const cv::Mat &H, const cv::Mat &K) override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
