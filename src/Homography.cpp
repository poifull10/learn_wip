
#include "Homography.h"

namespace wip {
cv::Mat HomographyEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const {
  return cv::findHomography(srcPoints, dstPoints);
}

std::tuple<float, std::vector<std::pair<cv::Point2f, cv::Point2f>>>
HomographyEstimator::evaluate(const cv::Mat &H,
                              std::vector<cv::Point2f> &srcPoints,
                              const std::vector<cv::Point2f> &dstPoints) {
  const auto srcPoints_ = H.inv() * convertToPoint2D(dstPoints);
  const auto dstPoints_ = H * convertToPoint2D(srcPoints);

  assert(srcPoints.size() == dstPoints.size());
  assert(srcPoints.size() == srcPoints_.size());
  assert(srcPoints.size() == dstPoints_.size());

  std::vector<std::pair<cv::Point2f, cv::Point2f>> inliners;

  float score = 0;
  for (size_t i = 0; i < srcPoints.size(); i++) {
    const auto subSrc   = srcPoints_[i].x() - srcPoints[i].x;
    const auto subDst   = dstPoints_[i].y() - dstPoints[i].y;
    const auto srcScore = evalFunc(cv::norm(subSrc));
    const auto dstScore = evalFunc(cv::norm(subDst));

    if (srcScore > 0 && dstScore > 0) {
      inliners.push_back(std::make_pair(srcPoints[i], dstPoints[i]));
    }
    score += srcScore + dstScore;
  }

  return {score, inliners};
}

float HomographyEstimator::evalFunc(const float val) const {
  const auto thresh = 5.99;
  const auto gamma  = 5.99;
  if (val < thresh) { return gamma - val; }

  return 0.f;
}

Pose HomographyEstimator::calcPose(const cv::Mat &H, const cv::Mat &K) {
  std::vector<cv::Mat> rotations, translations, normals;
  cv::decomposeHomographyMat(H, K, rotations, translations, normals);
  const auto [R, t] = validatePose(rotations, translations, K);
  return Pose(R, t);
}

} // namespace wip
