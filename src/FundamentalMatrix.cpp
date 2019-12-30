#include "FundamentalMatrix.h"
#include "RandomSampler.h"

namespace wip
{

cv::Mat FundamentalMatrixEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  return cv::findFundamentalMat(srcPoints, dstPoints, cv::FM_8POINT);
}

float FundamentalMatrixEstimator::evaluate(
  const cv::Mat &F, std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  const auto srcLines = F.inv() * convertToPoint2D(dstPoints);
  const auto dstLines = F * convertToPoint2D(srcPoints);

  assert(srcPoints.size() == dstPoints.size());
  assert(srcPoints.size() == srcLines.size());
  assert(srcPoints.size() == dstLines.size());

  float score = 0;
  for (size_t i = 0; i < srcPoints.size(); i++)
  {
    const auto subSrc = srcPoints_[i].x() - srcPoints[i].x;
    const auto subDst = dstPoints_[i].y() - dstPoints[i].y;
    score += evalFunc(cv::norm(subSrc)) + evalFunc(cv::norm(subDst));
  }

  return score;
}

float FundamentalMatrixEstimator::evalFunc(const float val) const
{
  const auto thresh = 3.84;
  const auto gamma = 5.99;
  if (threshDouble < val)
  {
    return gamma - val;
  }

  return 0.f;
}

Pose FundamentalMatrixEstimator::getPose(const cv::Mat &F) const
{
  // cv::decomposeHomographyMat(H);
  return Pose();
}
} // namespace wip
