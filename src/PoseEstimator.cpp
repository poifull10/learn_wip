#include <opencv2/opencv.hpp>

#include "PoseEstimator.h"
#include "RandomSampler.h"

#include <numeric>
#include <utility>

namespace wip
{
std::pair<float, cv::Mat> PoseEstimator::estimate() const
{
  float score = -std::numeric_limits<float>::max();
  cv::Mat H;

  for (size_t i = 0; i < ransacN_; i++)
  {
    RandomSampler rs(matches_.size());
    const auto [eightIndices, otherIndices] = rs.sample(8);

    assert(eightIndices.size() == 8);
    std::vector<cv::Point2f> srcPoints, dstPoints;
    for (const auto id : eightIndices)
    {
      const auto srcInd = matches_[id].trainIdx;
      const auto dstInd = matches_[id].queryIdx;
      srcPoints.push_back(srcKeyPoints_[srcInd].pt);
      dstPoints.push_back(dstKeyPoints_[dstInd].pt);
    }

    const auto H_ = calculate(srcPoints, dstPoints);
    const auto score_ = evaluate(H, srcPoints, dstPoints);
    if (score < score_)
    {
      score = score_;
      H = H_;
    }
  }

  return {score, H};
}
} // namespace wip
