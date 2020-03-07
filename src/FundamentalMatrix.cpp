#include "FundamentalMatrix.h"

#include "RandomSampler.h"

namespace wip
{

cv::Mat FundamentalMatrixEstimator::calculate(
  const std::vector<cv::Point2f> &srcPoints,
  const std::vector<cv::Point2f> &dstPoints) const
{
  return cv::findFundamentalMat(srcPoints, dstPoints, cv::FM_8POINT);
}

std::tuple<float, std::vector<std::pair<cv::Point2f, cv::Point2f>>>
FundamentalMatrixEstimator::evaluate(const cv::Mat &F,
                                     std::vector<cv::Point2f> &srcPoints,
                                     const std::vector<cv::Point2f> &dstPoints)
{
  assert(srcPoints.size() == dstPoints.size());
  std::vector<std::pair<cv::Point2f, cv::Point2f>> inliners;

  float score = 0;
  if (F.size().width == 0)
  {
    return {score, {}};
  }
  for (size_t i = 0; i < srcPoints.size(); i++)
  {
    float f0 = F.at<double>(cv::Point(0, 0));
    float f1 = F.at<double>(cv::Point(1, 0));
    float f2 = F.at<double>(cv::Point(2, 0));
    float f3 = F.at<double>(cv::Point(0, 1));
    float f4 = F.at<double>(cv::Point(1, 1));
    float f5 = F.at<double>(cv::Point(2, 1));
    float f6 = F.at<double>(cv::Point(0, 2));
    float f7 = F.at<double>(cv::Point(1, 2));
    float f8 = F.at<double>(cv::Point(2, 2));

    const auto aSrc = f0 * dstPoints[i].x + f3 * dstPoints[i].y + f6;
    const auto bSrc = f1 * dstPoints[i].x + f4 * dstPoints[i].y + f7;
    const auto cSrc = f2 * dstPoints[i].x + f5 * dstPoints[i].y + f8;
    const auto upperSqrtSrcScore =
      aSrc * srcPoints[i].x + bSrc * srcPoints[i].y + cSrc;
    const auto srcScore = evalFunc((upperSqrtSrcScore * upperSqrtSrcScore) /
                                   (aSrc * aSrc + bSrc * bSrc));

    const auto aDst = f0 * srcPoints[i].x + f1 * srcPoints[i].y + f2;
    const auto bDst = f3 * srcPoints[i].x + f4 * srcPoints[i].y + f5;
    const auto cDst = f6 * srcPoints[i].x + f7 * srcPoints[i].y + f8;
    const auto upperSqrtDstScore =
      aDst * dstPoints[i].x + bDst * dstPoints[i].y + cDst;
    const auto dstScore = evalFunc((upperSqrtDstScore * upperSqrtDstScore) /
                                   (aDst * aDst + bDst * bDst));

    if (srcScore > 0 && dstScore > 0)
    {
      inliners.push_back(std::make_pair(srcPoints[i], dstPoints[i]));
    }
    score += srcScore + dstScore;
  }

  return {score, inliners};
}

float FundamentalMatrixEstimator::evalFunc(const float val) const
{
  const auto thresh = 3.84;
  const auto gamma = 5.99;
  if (val < thresh)
  {
    return gamma - val;
  }

  return 0.f;
}

Pose FundamentalMatrixEstimator::calcPose(const cv::Mat &H, const cv::Mat &K)
{
  // cv::decomposeHomographyMat(H);
  return Pose();
}
} // namespace wip
