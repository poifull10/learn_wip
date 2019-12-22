#include "PoseInitializer.h"
#include "RandomSampler.h"

#include <cassert>
#include <numeric>

namespace wip
{
Pose PoseInitializer::operator()(const Image &src, const Image &dst) const
{
  const auto [kpSrc, dsSrc] = featureExtractor_(src);
  const auto [kpDst, dsDst] = featureExtractor_(dst);

  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(dsSrc, dsDst, matches);

  if (matches.size() < 8)
  {
    return Pose();
  }

  // RANSAC

  // Estimate H, F

  // Select H, F

  return Pose();
}

std::pair<float, cv::Mat> PoseInitializer::estimateHomography(
  const std::vector<cv::DMatch> &matches,
  const std::vector<cv::KeyPoint> &srcKeyPoints,
  const std::vector<cv::KeyPoint> &dstKeyPoints)
{
  float score = -std::numeric_limits<float>::max();
  cv::Mat H;

  for (size_t i = 0; i < ransac_n_; i++)
  {
    RandomSampler rs(matches.size());
    const auto [eightIndices, otherIndices] = rs.sample(8);

    assert(eightIndices.size() == 8);
    std::vector<cv::Point2f> srcPoints, dstPoints;
    for (const auto id : eightIndices)
    {
      const auto srcInd = matches[id].trainIdx;
      const auto dstInd = matches[id].queryIdx;
      srcPoints.push_back(srcKeyPoints[srcInd].pt);
      dstPoints.push_back(dstKeyPoints[dstInd].pt);
    }

    // const auto H_ = calcHomography(srcPoints, dstPoints);
  }

  return {score, H};
}

} // namespace wip
