#include "PoseInitializer.h"

namespace wip
{
Pose PoseInitializer::operator()(const Image &src, const Image &dst) const
{
  const auto [kpSrc, dsSrc] = featureExtractor_(src);
  const auto [kpDst, dsDst] = featureExtractor_(dst);

  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(dsSrc, dsDst, matches);

  // Ransac

  // Estimate H, F

  // Select H, F

  return Pose();
}
} // namespace wip