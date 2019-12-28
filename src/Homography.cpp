
#include "Homography.h"
#include "RandomSampler.h"

namespace wip
{

std::pair<float, cv::Mat> HomographyEstimator::estimate() const
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

float HomographyEstimator::evaluate(
  const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  const auto srcPoints_ = H.inv() * convertToPoint2D(dstPoints);
  const auto dstPoints_ = H * convertToPoint2D(srcPoints);

  assert(srcPoints.size() == dstPoints.size());
  assert(srcPoints.size() == srcPoints_.size());
  assert(srcPoints.size() == dstPoints_.size());

  float score = 0;
  for (size_t i = 0; i < srcPoints.size(); i++)
  {
    const auto subSrc = srcPoints_[i].x() - srcPoints[i].x;
    const auto subDst = dstPoints_[i].y() - dstPoints[i].y;
    score += evalFunc(cv::norm(subSrc)) + evalFunc(cv::norm(subDst));
  }

  return score;
}

float HomographyEstimator::evalFunc(const float val) const
{
  const auto threshDouble = thresh_ * thresh_;
  if (threshDouble < val)
  {
    return threshDouble - val;
  }

  return 0.f;
}

Pose HomographyEstimator::getPose(const cv::Mat &H) const
{
  // cv::decomposeHomographyMat(H);
  return Pose();
}

} // namespace wip
