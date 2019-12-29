#pragma once

#include "PoseEstimator.h"

namespace wip
{
class HomographyEstimator : public PoseEstimator
{
public:
  HomographyEstimator(const std::vector<cv::DMatch> &matches,
                      const std::vector<cv::KeyPoint> &srcKeyPoints,
                      const std::vector<cv::KeyPoint> &dstKeyPoints,
                      size_t ransacN = 30, float thresh = 2.44765f)
    : PoseEstimator(matches, srcKeyPoints, dstKeyPoints, ransacN, thresh)
  {
  }

  HomographyEstimator(size_t ransacN = 30, float thresh = 2.44765f)
    : PoseEstimator(ransacN_, thresh)
  {
  }

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                 const std::vector<cv::Point2f> &dstPoints) const override;

  Pose getPose(const cv::Mat &H) const override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
