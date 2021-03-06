#include "FundamentalMatrix.h"

#include "RandomSampler.h"

namespace wip {

cv::Mat FundamentalMatrixEstimator::calculate(
  const std::vector<cv::Point2d> &srcPoints,
  const std::vector<cv::Point2d> &dstPoints) const {
  return cv::findFundamentalMat(srcPoints, dstPoints, cv::FM_8POINT);
}

std::tuple<double, std::vector<std::pair<cv::Point2d, cv::Point2d>>>
FundamentalMatrixEstimator::evaluate(
  const cv::Mat &F, std::vector<cv::Point2d> &srcPoints,
  const std::vector<cv::Point2d> &dstPoints) {
  assert(srcPoints.size() == dstPoints.size());
  std::vector<std::pair<cv::Point2d, cv::Point2d>> inliners;

  double score = 0;
  if (F.size().width == 0) { return {score, {}}; }
  for (size_t i = 0; i < srcPoints.size(); i++) {
    double f0 = F.at<double>(cv::Point(0, 0));
    double f1 = F.at<double>(cv::Point(1, 0));
    double f2 = F.at<double>(cv::Point(2, 0));
    double f3 = F.at<double>(cv::Point(0, 1));
    double f4 = F.at<double>(cv::Point(1, 1));
    double f5 = F.at<double>(cv::Point(2, 1));
    double f6 = F.at<double>(cv::Point(0, 2));
    double f7 = F.at<double>(cv::Point(1, 2));
    double f8 = F.at<double>(cv::Point(2, 2));

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

    if (srcScore > 0 && dstScore > 0) {
      inliners.push_back(std::make_pair(srcPoints[i], dstPoints[i]));
    }
    score += srcScore + dstScore;
  }

  return {score, inliners};
}

double FundamentalMatrixEstimator::evalFunc(const double val) const {
  const auto thresh = 3.84;
  const auto gamma  = 5.99;
  if (val < thresh) { return gamma - val; }

  return 0.f;
}

Pose FundamentalMatrixEstimator::calcPose(const cv::Mat &F, const cv::Mat &K) {
  cv::Mat R1, R2, T;
  const cv::Mat E = K.inv().t() * F * K.inv();
  cv::decomposeEssentialMat(E, R1, R2, T);
  const auto [R, t] = validatePose({R1, R2}, {T, T}, K);
  return Pose(R, t);
}
} // namespace wip
