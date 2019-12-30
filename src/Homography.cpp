
#include "Homography.h"

namespace wip
{
cv::Mat HomographyEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  return cv::findHomography(srcPoints, dstPoints);
}

float HomographyEstimator::evaluate(
  const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  const auto srcPoints_ = H.inv() * convertToPoint2D(dstPoints);
  const auto dstPoints_ = H * convertToPoint2D(srcPoints);

  assert(srcPoints.size() == dstPoints.size());
  assert(srcPoints.size() == srcPoints_.size());
  assert(srcPoints.size() == dstPoints_.size());

  float score = 0;
  for (size_t i = 0; i < srcPoints.size(); i++)
  {
    const auto subSrc = srcPoints_[i].x() - srcPoints[i].x;
    const auto subDst = dstPoints_[i].y() - dstPoints[i].y;
    score += evalFunc(cv::norm(subSrc)) + evalFunc(cv::norm(subDst));
  }

  return score;
}

float HomographyEstimator::evalFunc(const float val) const
{
  const auto thresh = 5.99;
  const auto gamma = 5.99;
  if (val < thresh)
  {
    return gamma - val;
  }

  return 0.f;
}

Pose HomographyEstimator::getPose(const cv::Mat &H, const cv::Mat &K,
                                  const std::vector<cv::Point2f> &src,
                                  const std::vector<cv::Point2f> &dst) const
{
  std::vector<cv::Mat> rotations, translations, normals;
  cv::decomposeHomographyMat(H, K, rotations, translations, normals);

  for (size_t i = 0; i < rotations.size(); i++)
  {
    cv::Mat triangluatedPointsInHomogeneous;
    cv::triangulatePoints(
      compositeProjectionMatrix(K, cv::Mat::eye(3, 3, CV_32F),
                                cv::Mat::zeros(3, 1, CV_32F)),
      compositeProjectionMatrix(K, rotations[i], translations[i]), src, dst,
      triangluatedPointsInHomogeneous);
    std::cout << triangluatedPointsInHomogeneous << std::endl;
  }

  return Pose();
}

} // namespace wip
