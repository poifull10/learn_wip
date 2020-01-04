
#include "Homography.h"

namespace wip
{
cv::Mat HomographyEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  return cv::findHomography(srcPoints, dstPoints);
}

float HomographyEstimator::evaluate(const cv::Mat &H,
                                    std::vector<cv::Point2f> &srcPoints,
                                    const std::vector<cv::Point2f> &dstPoints)
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
    const auto srcScore = evalFunc(cv::norm(subSrc));
    const auto dstScore = evalFunc(cv::norm(subDst));

    if (srcScore > 0 && dstScore > 0)
    {
      inliners_.push_back(std::make_pair(srcPoints[i], dstPoints[i]));
    }
    score += srcScore + dstScore;
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

Pose HomographyEstimator::calcPose(const cv::Mat &H, const cv::Mat &K,
                                   const std::vector<cv::Point2f> &src,
                                   const std::vector<cv::Point2f> &dst) const
{
  std::vector<cv::Mat> rotations, translations, normals;
  cv::decomposeHomographyMat(H, K, rotations, translations, normals);

  int valid = 0;
  for (size_t i = 0; i < rotations.size(); i++)
  {
    cv::Mat triangluatedPointsInHomogeneous;
    cv::triangulatePoints(
      compositeProjectionMatrix(K, cv::Mat::eye(3, 3, CV_32F),
                                cv::Mat::zeros(3, 1, CV_32F)),
      compositeProjectionMatrix(K, rotations[i], translations[i]), src, dst,
      triangluatedPointsInHomogeneous);
    bool isValid = true;
    for (size_t j = 0; j < triangluatedPointsInHomogeneous.cols; j++)
    {
      if (triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 2)) /
            triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 3)) >
          0)
      {
        const auto x =
          triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 0));
        const auto y =
          triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 1));
        const auto z =
          triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 2));
        const auto w =
          triangluatedPointsInHomogeneous.at<float>(cv::Point(j, 3));
        cv::Point3f p(x / w, y / w, z / w);
        if (cv::Point3f(normals[i]).dot(p) > 0)
        {
          isValid &= true;
        }
        else
        {
          isValid &= false;
        }
      }
      else
      {
        isValid &= false;
      }
    }
    if (isValid)
    {
      valid++;
      std::cout << rotations[i] << std::endl;
      std::cout << translations[i] << std::endl;
      std::cout << normals[i] << std::endl;
    }
  }
  std::cout << "Hypothesis: " << rotations.size() << std::endl;
  std::cout << "Valid: " << valid << std::endl;

  return Pose();
}

} // namespace wip
