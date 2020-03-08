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
  const auto matched = fm({kpSrc, dsSrc}, {kpDst, dsDst});

  std::cout << matched.size() << " matches found" << std::endl;

  if (matched.size() < 8)
  {
    std::cout << "Initialization is failed, retry initialization." << std::endl;
    return Pose();
  }

  wip::HomographyEstimator he(ransac_n_);
  wip::FundamentalMatrixEstimator fme(ransac_n_);

  const auto [hScore, H] = he.estimate(matched);
  const auto [fScore, F] = fme.estimate(matched);

  // Select H, F
  std::cout << "hScore " << hScore << std::endl;
  std::cout << "fScore " << fScore << std::endl;

  // std::cout << he.calcPose();
  std::cout << H << std::endl;
  std::cout << src.cameraParameter_.K() << std::endl;

  const auto pose = he.calcPose(H, src.cameraParameter_.K());

  return pose;
}

} // namespace wip
