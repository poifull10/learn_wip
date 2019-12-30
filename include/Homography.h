#pragma once

#include "PoseEstimator.h"

namespace wip
{
class HomographyEstimator : public PoseEstimator
{
public:
  HomographyEstimator(size_t ransacN = 30) : PoseEstimator(ransacN_) {}

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                 const std::vector<cv::Point2f> &dstPoints) const override;

  Pose getPose(const cv::Mat &H, const cv::Mat &K) const override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
