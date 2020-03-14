#pragma once

#include "PoseEstimator.h"

namespace wip {
class HomographyEstimator : public PoseEstimator {
public:
  HomographyEstimator(size_t ransacN = 30) : PoseEstimator(ransacN) {}

  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const override;

  std::tuple<float, std::vector<std::pair<cv::Point2f, cv::Point2f>>>
  evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
           const std::vector<cv::Point2f> &dstPoints) override;

  Pose calcPose(const cv::Mat &H, const cv::Mat &K) override;

private:
  float evalFunc(const float val) const;
};
} // namespace wip
