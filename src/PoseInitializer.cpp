#include "PoseInitializer.h"

#include <cassert>
#include <numeric>

#include "FeatureMatcher.h"
#include "FundamentalMatrix.h"
#include "Homography.h"
#include "RandomSampler.h"

namespace wip {
std::optional<Pose> PoseInitializer::operator()(Frame &src, Frame &dst) const {
  const auto srcKptDsc = featureExtractor_(src.image());
  const auto dstKptDsc = featureExtractor_(dst.image());

  FeatureMatcher fm;
  const auto matched = fm(srcKptDsc, dstKptDsc);

  std::cout << matched.size() << " matches found" << std::endl;

  if (matched.size() < 8) {
    std::cout << "Initialization is failed, retry initialization." << std::endl;
    return std::nullopt;
  }

  HomographyEstimator he(ransac_n_);
  FundamentalMatrixEstimator fme(ransac_n_);

  const auto [hScore, H] = he.estimate(matched);
  const auto [fScore, F] = fme.estimate(matched);

  // Select H, F
  std::cout << "hScore " << hScore << std::endl;
  std::cout << "fScore " << fScore << std::endl;

  if (hScore / (hScore + fScore) > 0.4) {
    return he.calcPose(H, src.cameraParameter_.K());
  }
  return fme.calcPose(F, src.cameraParameter_.K());
}

} // namespace wip
