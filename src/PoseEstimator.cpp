#include <opencv2/opencv.hpp>

#include "PoseEstimator.h"
#include "RandomSampler.h"

#include <numeric>
#include <utility>

namespace wip
{
std::pair<float, cv::Mat> PoseEstimator::estimate(
  const std::vector<cv::DMatch> &matches,
  const std::vector<cv::KeyPoint> &srcKeyPoints,
  const std::vector<cv::KeyPoint> &dstKeyPoints)
{
  float score = -std::numeric_limits<float>::max();
  cv::Mat H;

  for (size_t i = 0; i < ransacN_; i++)
  {
    RandomSampler rs(matches.size());
    const auto [eightIndices, otherIndices] = rs.sample(8);

    assert(eightIndices.size() == 8);
    std::vector<cv::Point2f> srcMatchedPoints, dstMatchedPoints;
    for (const auto &id : eightIndices)
    {
      const auto srcInd = matches[id].trainIdx;
      const auto dstInd = matches[id].queryIdx;
      srcMatchedPoints.push_back(srcKeyPoints[srcInd].pt);
      dstMatchedPoints.push_back(dstKeyPoints[dstInd].pt);
    }

    const auto H_ = calculate(srcMatchedPoints, dstMatchedPoints);

    std::vector<cv::Point2f> evalSrcMatchedPoints, evalDstMatchedPoints;
    for (const auto &match : matches)
    {
      evalSrcMatchedPoints.push_back(srcKeyPoints[match.trainIdx].pt);
      evalDstMatchedPoints.push_back(dstKeyPoints[match.queryIdx].pt);
    }

    const auto score_ =
      evaluate(H_, evalSrcMatchedPoints, evalDstMatchedPoints);
    if (score < score_)
    {
      score = score_;
      H = H_;
    }
  }

  return {score, H};
}

cv::Mat compositeProjectionMatrix(const cv::Mat &K, const cv::Mat &R,
                                  const cv::Mat &t)
{
  cv::Mat outerMat = cv::Mat::zeros(3, 4, CV_32F);
  R.copyTo(outerMat(cv::Rect(0, 0, 3, 3)));
  t.copyTo(outerMat(cv::Rect(3, 0, 1, 3)));
  return K * outerMat;
}

bool checkRules(const cv::Mat &p3d, const cv::Mat &R, const cv::Mat &t)
{
  cv::Mat reconstructedPoint1 = p3d;
  cv::Mat R_ = R;
  R_.convertTo(R_, CV_32F);
  cv::Mat t_ = t;
  t_.convertTo(t_, CV_32F);

  cv::Mat O1 = cv::Mat::zeros(3, 1, CV_32F);
  cv::Mat O2 = -R_.t() * t_;
  O2.convertTo(O2, CV_32F);

  cv::Mat normal1 = reconstructedPoint1 - O1;
  cv::Mat normal2 = reconstructedPoint1 - O2;

  auto parallax =
    normal1.dot(normal2) / (cv::norm(normal1) * cv::norm(normal2));

  if (parallax < 0.99998 && reconstructedPoint1.at<float>(2, 0) < 0)
  {
    return false;
  }

  cv::Mat reconstructedPoint2 = R_ * reconstructedPoint1 + t_;
  reconstructedPoint2.convertTo(reconstructedPoint2, CV_32F);
  normal1 = reconstructedPoint2 - O1;
  normal2 = reconstructedPoint2 - O2;

  parallax = normal1.dot(normal2) / (cv::norm(normal1) * cv::norm(normal2));

  if (parallax < 0.99998 && reconstructedPoint2.at<float>(2, 0) < 0)
  {
    return false;
  }
  return true;
}

std::pair<cv::Mat, cv::Mat> PoseEstimator::validatePose(
  const std::vector<cv::Mat> &rotations,
  const std::vector<cv::Mat> &translations, const cv::Mat &K)
{

  float bestError = std::numeric_limits<float>::max();
  cv::Mat R, t;
  for (size_t i = 0; i < rotations.size(); i++)
  {
    cv::Mat P1 = compositeProjectionMatrix(K, cv::Mat::eye(3, 3, CV_32F),
                                           cv::Mat::zeros(3, 1, CV_32F));
    cv::Mat P2 = compositeProjectionMatrix(K, rotations[i], translations[i]);
    P1.convertTo(P1, CV_32F);
    P2.convertTo(P2, CV_32F);

    for (size_t j = 0; j < inliners_.size(); j++)
    {
      std::cout << j << std::endl;
      const auto [src, dst] = inliners_[j];
      cv::Mat A(4, 4, CV_32F);

      A.row(0) = src.x * P1.row(2) - P1.row(0);
      A.row(1) = src.y * P1.row(2) - P1.row(1);
      A.row(2) = dst.x * P2.row(2) - P2.row(0);
      A.row(3) = dst.y * P2.row(2) - P2.row(1);

      cv::Mat u, w, vt;
      cv::SVD::compute(A, w, u, vt, cv::SVD::MODIFY_A | cv::SVD::FULL_UV);
      cv::Mat x3D = vt.row(3).t();
      x3D = x3D.rowRange(0, 3) / x3D.at<float>(3);

      std::cout << x3D << std::endl;
      const cv::Mat reconstructedPoint = x3D;

      if (!checkRules(reconstructedPoint, rotations[i], translations[i]))
      {
        break;
      }

      const cv::Mat projectedPoint1 =
        P1 * reconstructedPoint / (reconstructedPoint * x3D).col(2);
      const cv::Mat projectedPoint2 =
        P2 * reconstructedPoint / (reconstructedPoint * x3D).col(2);

      const auto x1 = projectedPoint1.at<float>(0, 0);
      const auto y1 = projectedPoint1.at<float>(1, 0);
      const auto x2 = projectedPoint2.at<float>(0, 0);
      const auto y2 = projectedPoint2.at<float>(1, 0);

      const auto reprojectedError =
        (x1 - src.x) * (y1 - src.y) + (x2 - dst.x) * (y2 - dst.y);

      if (reprojectedError < bestError)
      {
        bestError = reprojectedError;
        R = rotations[i];
        t = translations[i];
      }
    }
  }
  return {R, t};
}
} // namespace wip
