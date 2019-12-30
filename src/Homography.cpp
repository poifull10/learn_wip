
#include "Homography.h"

namespace wip
{
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
  const auto thresh = 5.99;
  const auto gamma = 5.99;
  if (thresh < val)
  {
    return gamma - val;
  }

  return 0.f;
}

Pose HomographyEstimator::getPose(const cv::Mat &H) const
{
  // cv::decomposeHomographyMat(H);
  return Pose();
}

} // namespace wip
