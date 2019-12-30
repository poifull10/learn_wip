#include "PoseInitializer.h"
#include "FundamentalMatrix.h"
#include "Homography.h"
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
  const auto dm = cv::DescriptorMatcher::create("FlannBased");
  dm->match(dsSrc, dsDst, matches);

  std::cout << matches.size() << " matches found" << std::endl;

  if (matches.size() < 8)
  {
    std::cout << "Initialization is failed, retry initialization." << std::endl;
    return Pose();
  }

  wip::HomographyEstimator he;
  wip::FundamentalMatrixEstimator fme;

  const auto [hScore, H] = he.estimate(matches, kpSrc, kpDst);
  const auto [fScore, F] = fme.estimate(matches, kpSrc, kpDst);

  // Select H, F
  std::cout << "hScore " << hScore << std::endl;
  std::cout << "fScore " << fScore << std::endl;

  return Pose();
}

} // namespace wip
