
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

float HomographyEstimator::evaluate(
  cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  // auto src = cv::Mat(srcPoints).reshape(1, 2).t();
  // auto dst = cv::Mat(dstPoints).reshape(1, 2).t();
  // std::vector<cv::Point3f> src;
  // std::vector<cv::Point3f> dst;
  // cv::convertPointsToHomogeneous(srcPoints, src);
  // cv::convertPointsToHomogeneous(dstPoints, dst);
  // auto estimatedSrcPoints = H.inv() * dst;
  // auto estimatedDstPoints = H * src;
  // cv::convertPointsFromHomogeneous(estimatedSrcPoints, estimatedSrcPoints);
  // cv::convertPointsFromHomogeneous(estimatedDstPoints, estimatedDstPoints);

  // const auto subSrc = src - estimatedSrcPoints;
  // const auto subDst = dst - estimatedDstPoints;

  float score = 0;
  // for (size_t h = 0; h < srcPoints.size(); h++)
  // {
  //   score +=
  //     evalFunc(cv::norm(subSrc.row(h))) + evalFunc(cv::norm(subDst.row(h)));
  // }
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

} // namespace wip
