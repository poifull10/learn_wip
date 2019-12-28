#pragma once

#include "PoseEstimator.h"

namespace wip
{
class FundamentalMatrixEstimator : public PoseEstimator
{
public:
  FundamentalMatrixEstimator(const std::vector<cv::DMatch> &matches,
                             const std::vector<cv::KeyPoint> &srcKeyPoints,
                             const std::vector<cv::KeyPoint> &dstKeyPoints,
                             size_t ransacN = 30, float thresh = 2.44765f)
    : PoseEstimator(matches, srcKeyPoints, dstKeyPoints, ransacN, thresh)
  {
  }

  FundamentalMatrixEstimator(size_t ransacN = 30, float thresh = 2.44765f)
    : HomographyEstimator(ransacN_, thresh)
  {
  }

private:
};
} // namespace wip
