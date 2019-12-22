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
  // Select 8 points
  for (size_t i = 0; i < ransac_n_; i++)
  {
    std::uniform_int_distribution randInt(0, static_cast<int>(matches.size())-1);
  }
  // Estimate H, F

  // Select H, F

  return Pose();
}
} // namespace wip
