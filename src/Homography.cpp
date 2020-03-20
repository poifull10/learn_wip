
#include "Homography.h"

namespace wip {
cv::Mat HomographyEstimator::calculate(
  const std::vector<cv::Point2d> &srcPoints,
  const std::vector<cv::Point2d> &dstPoints) const {
  return cv::findHomography(srcPoints, dstPoints);
}

std::tuple<double, std::vector<std::pair<cv::Point2d, cv::Point2d>>>
HomographyEstimator::evaluate(const cv::Mat &H,
                              const std::vector<cv::Point2d> &srcPoints,
                              const std::vector<cv::Point2d> &dstPoints) {
  const auto srcPoints_ = H.inv() * convertToPoint2D(dstPoints);
  const auto dstPoints_ = H * convertToPoint2D(srcPoints);

  assert(srcPoints.size() == dstPoints.size());
  assert(srcPoints.size() == srcPoints_.size());
  assert(srcPoints.size() == dstPoints_.size());

  std::vector<std::pair<cv::Point2d, cv::Point2d>> inliners;

  double score = 0;
  for (size_t i = 0; i < srcPoints.size(); i++) {
    const auto subSrc   = srcPoints_[i] - srcPoints[i];
    const auto subDst   = dstPoints_[i] - dstPoints[i];
    const auto srcScore = evalFunc(cv::norm(subSrc.point()));
    const auto dstScore = evalFunc(cv::norm(subDst.point()));

    if (srcScore > 0 && dstScore > 0) {
      inliners.push_back(std::make_pair(srcPoints[i], dstPoints[i]));
    }
    score += srcScore + dstScore;
  }

  return {score, inliners};
}

double HomographyEstimator::evalFunc(const double val) const {
  const auto thresh = 5.99;
  const auto gamma  = 5.99;
  if (val < thresh) { return gamma - val; }

  return 0.f;
}

Pose HomographyEstimator::calcPose(const cv::Mat &H, const cv::Mat &K) {
  std::vector<cv::Mat> rotations, translations, normals;
  cv::decomposeHomographyMat(H, K, rotations, translations, normals);
  for (size_t i = 0; i < rotations.size(); i++) {
    std::cout << "Estimate Pose == " << std::endl;
    std::cout << rotations[i] << std::endl;
    std::cout << translations[i] / cv::norm(translations[i]) << std::endl;
  }
  const auto [R, t] = validatePose(rotations, translations, K);
  const auto t_norm = cv::norm(t);
  return Pose(R, t / t_norm);
}

} // namespace wip
