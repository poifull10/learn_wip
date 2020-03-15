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
  std::cout << "H Inlier : " << he.inliers().size() << std::endl;
  std::cout << "F Inlier : " << fme.inliers().size() << std::endl;

  const auto [kp, _] = srcKptDsc;
  std::vector<cv::KeyPoint> dstKp;
  std::vector<cv::DMatch> _matches;
  for (size_t k = 0; k < kp.size(); k++) {
    _matches.push_back(cv::DMatch(k, k, 0));
    cv::Point2d p(kp[k].pt);
    const auto p_ = H * convertToPoint2D({p});
    dstKp.push_back(cv::KeyPoint(p_[0].point().x, p_[0].point().y, 1));
  }
  cv::Mat oImg;
  cv::drawMatches(src.image().data(), kp, dst.image().data(), dstKp, _matches,
                  oImg);
  cv::imwrite("homo.png", oImg);

  return he.calcPose(H, src.cameraParameter_.K());

  // if (hScore / (hScore + fScore) > 0.4) {
  //   std::cout << "Inlier : " << he.inliers().size() << std::endl;
  //   return he.calcPose(H, src.cameraParameter_.K());
  // }
  // std::cout << "Inlier : " << fme.inliers().size() << std::endl;
  // return fme.calcPose(F, src.cameraParameter_.K());
}

} // namespace wip
