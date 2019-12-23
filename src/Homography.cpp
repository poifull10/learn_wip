
#include "Homography.h"
#include "RandomSampler.h"

namespace wip
{

std::pair<float, cv::Mat> HomographyEstimator::estimate()
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
  }

  return {score, H};
}

cv::Mat HomographyEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  return cv::findHomography(srcPoints, dstPoints);
}

float HomographyEstimator::evalueate(
  const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  // const auto estimatedDstPoints = H * srcPoints;
  return 0;
}

} // namespace wip
