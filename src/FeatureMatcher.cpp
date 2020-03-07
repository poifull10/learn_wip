#include "FeatureMatcher.h"

namespace wip
{
std::vector<cv::DMatch> FeatureMatcher::operator()(const cv::Mat& srcDesc,
                                                   const cv::Mat& dstDesc) const
{
  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(dstDesc, srcDesc, matches);
  return matches;
}
} // namespace wip
