#include <opencv2/opencv.hpp>

#include "PoseEstimator.h"
#include "RandomSampler.h"

#include <numeric>
#include <utility>

namespace wip
{
std::pair<float, cv::Mat> PoseEstimator::estimate(
  const std::vector<cv::DMatch> &matches,
  const std::vector<cv::KeyPoint> &srcKeyPoints,
  const std::vector<cv::KeyPoint> &dstKeyPoints) const
{
  float score = -std::numeric_limits<float>::max();
  cv::Mat H;

  for (size_t i = 0; i < ransacN_; i++)
  {
    RandomSampler rs(matches.size());
    const auto [eightIndices, otherIndices] = rs.sample(8);

    assert(eightIndices.size() == 8);
    std::vector<cv::Point2f> srcMatchedPoints, dstMatchedPoints;
    for (const auto &id : eightIndices)
    {
      const auto srcInd = matches[id].trainIdx;
      const auto dstInd = matches[id].queryIdx;
      srcMatchedPoints.push_back(srcKeyPoints[srcInd].pt);
      dstMatchedPoints.push_back(dstKeyPoints[dstInd].pt);
    }

    const auto H_ = calculate(srcMatchedPoints, dstMatchedPoints);

    std::vector<cv::Point2f> evalSrcMatchedPoints, evalDstMatchedPoints;
    for (const auto &match : matches)
    {
      evalSrcMatchedPoints.push_back(srcKeyPoints[match.trainIdx].pt);
      evalDstMatchedPoints.push_back(dstKeyPoints[match.queryIdx].pt);
    }

    const auto score_ = evaluate(H, evalSrcMatchedPoints, evalDstMatchedPoints);
    if (score < score_)
    {
      score = score_;
      H = H_;
    }
  }

  return {score, H};
}

cv::Mat compositeProjectionMatrix(const cv::Mat &K, const cv::Mat &R,
                                  const cv::Mat &t)
{
  cv::Mat outerMat = cv::Mat::zeros(cv::Size(4, 3), CV_32F);
  R.copyTo(outerMat(cv::Rect(0, 0, 3, 3)));
  t.copyTo(outerMat(cv::Rect(3, 0, 1, 3)));
  return K * outerMat;
}

} // namespace wip
