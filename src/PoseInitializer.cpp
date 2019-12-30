#include "PoseInitializer.h"
#include "FundamentalMatrix.h"
#include "Homography.h"
#include "RandomSampler.h"

#include <cassert>
#include <numeric>

namespace wip
{
Pose PoseInitializer::operator()(Frame &src, Frame &dst) const
{
  const auto [kpSrc, dsSrc] = featureExtractor_(src.image());
  const auto [kpDst, dsDst] = featureExtractor_(dst.image());

  std::vector<cv::DMatch> matches;
  const auto dm = cv::DescriptorMatcher::create("BruteForce-Hamming");
  dm->match(dsSrc, dsDst, matches);

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
  // std::cout << he.calcPose(H, );

  return Pose();
}

} // namespace wip
