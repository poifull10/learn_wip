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
  std::cout << "H Score " << hScore << std::endl;
  std::cout << "F Score " << fScore << std::endl;
  std::cout << "H Inlier : " << he.inliers().size() << std::endl;
  std::cout << "F Inlier : " << fme.inliers().size() << std::endl;

  cv::Mat oImg;
  const auto usedSrcPoints = fme.usedSrcPoints();
  const auto usedDstPoints = fme.usedDstPoints();
  std::vector<cv::KeyPoint> usedSrcKeyPoints, usedDstKeyPoints;
  std::vector<cv::DMatch> usedMatches;
  for (size_t k = 0; k < usedSrcPoints.size(); k++) {
    usedSrcKeyPoints.push_back(
      cv::KeyPoint(usedSrcPoints[k].x, usedSrcPoints[k].y, 1));
    usedDstKeyPoints.push_back(
      cv::KeyPoint(usedDstPoints[k].x, usedDstPoints[k].y, 1));
    usedMatches.push_back(cv::DMatch(k, k, 0));
  }

  cv::drawMatches(src.image().data(), usedSrcKeyPoints, dst.image().data(),
                  usedDstKeyPoints, usedMatches, oImg);
  cv::imwrite("usedPoints.png", oImg);

  return fme.calcPose(H, src.cameraParameter_.K());

  // if (hScore / (hScore + fScore) > 0.4) {
  //   std::cout << "Inlier : " << he.inliers().size() << std::endl;
  //   return he.calcPose(H, src.cameraParameter_.K());
  // }
  // std::cout << "Inlier : " << fme.inliers().size() << std::endl;
  // return fme.calcPose(F, src.cameraParameter_.K());
}

} // namespace wip
