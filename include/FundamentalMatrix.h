#pragma once

#include "PoseEstimator.h"

#include <utility>

namespace wip
{
class FundamentalMatrixEstimator : public PoseEstimator
{
public:
  FundamentalMatrixEstimator(size_t ransacN = 30) : PoseEstimator(ransacN) {}

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  float evaluate(const cv::Mat &F, std::vector<cv::Point2f> &srcPoints,
                 const std::vector<cv::Point2f> &dstPoints) override;

  Pose calcPose(const cv::Mat &H, const cv::Mat &K) override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
