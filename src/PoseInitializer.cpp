#include "PoseInitializer.h"

#include <cassert>
#include <numeric>

#include "FeatureMatcher.h"
#include "FundamentalMatrix.h"
#include "Homography.h"
#include "OpenCVUtils.h"
#include "RandomSampler.h"

namespace wip
{
Pose PoseInitializer::operator()(Frame &src, Frame &dst) const
{
  const auto [kpSrc, dsSrc] = featureExtractor_(src.image());
  const auto [kpDst, dsDst] = featureExtractor_(dst.image());

  wip::FeatureMatcher fm;
  const auto matches = fm(dsSrc, dsDst);

  std::cout << matches.size() << " matches found" << std::endl;

  if (matches.size() < 8)
  {
    std::cout << "Initialization is failed, retry initialization." << std::endl;
    return Pose();
  }

  wip::HomographyEstimator he(ransac_n_);
  wip::FundamentalMatrixEstimator fme(ransac_n_);

  const auto [hScore, H] = he.estimate(matches, kpSrc, kpDst);
  const auto [fScore, F] = fme.estimate(matches, kpSrc, kpDst);

  // Select H, F
  std::cout << "hScore " << hScore << std::endl;
  std::cout << "fScore " << fScore << std::endl;

  // std::cout << he.calcPose();
  const auto [matchedSrc, matchedDst] =
    wip::getMatchedPoints(matches, kpSrc, kpDst);

  std::cout << H << std::endl;
  std::cout << src.cameraParameter_.K() << std::endl;

  const auto pose = he.calcPose(H, src.cameraParameter_.K());

  return pose;
}

} // namespace wip
