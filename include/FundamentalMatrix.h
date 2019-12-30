#pragma once

#include "PoseEstimator.h"

#include <utility>

namespace wip
{
class FundamentalMatrixEstimator : public PoseEstimator
{
public:
  FundamentalMatrixEstimator(size_t ransacN = 30) : PoseEstimator(ransacN_) {}

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  float evaluate(const cv::Mat &F, std::vector<cv::Point2f> &srcPoints,
                 const std::vector<cv::Point2f> &dstPoints) const override;

  Pose getPose(const cv::Mat &H, const cv::Mat &K,
               const std::vector<cv::Point2f> &src,
               const std::vector<cv::Point2f> &dst) const override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
