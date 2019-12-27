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

} // namespace wip
