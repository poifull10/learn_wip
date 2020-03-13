#include "FeatureMatcher.h"

namespace wip
{

std::vector<std::tuple<cv::KeyPoint, cv::KeyPoint>> FeatureMatcher::operator()(
  const std::tuple<std::vector<cv::KeyPoint>, cv::Mat>& src,
  const std::tuple<std::vector<cv::KeyPoint>, cv::Mat>& dst)
{

  const auto [src_kpts, src_desc] = src;
  const auto [dst_kpts, dst_desc] = dst;

  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(dst_desc, src_desc, matches_);

  std::vector<std::tuple<cv::KeyPoint, cv::KeyPoint>> keypoints;

  for (const auto& match : matches_)
  {
    keypoints.emplace_back(src_kpts[match.trainIdx], dst_kpts[match.queryIdx]);
  }

  return keypoints;
}
} // namespace wip
