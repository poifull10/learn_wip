#pragma once

#include <opencv2/opencv.hpp>

#include "Point.h"
#include "Pose.h"

#include <utility>
#include <vector>

namespace wip
{
class PoseEstimator
{
public:
  PoseEstimator(const std::vector<cv::DMatch> &matches,
                const std::vector<cv::KeyPoint> &srcKeyPoints,
                const std::vector<cv::KeyPoint> &dstKeyPoints,
                size_t ransacN = 30, float thresh = 2.44765f)
    : matches_(matches)
    , srcKeyPoints_(srcKeyPoints)
    , dstKeyPoints_(dstKeyPoints)
    , ransacN_(ransacN)
    , thresh_(thresh)
  {
  }

  PoseEstimator(size_t ransacN = 30, float thresh = 2.44765f)
    : matches_()
    , srcKeyPoints_()
    , dstKeyPoints_()
    , ransacN_(ransacN)
    , thresh_(thresh)
  {
  }

  std::pair<float, cv::Mat> estimate() const;

  virtual cv::Mat calculate(
    const std::vector<cv::Point2f> &srcPoints,
    const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                         const std::vector<cv::Point2f> &dstPoints) const = 0;

  virtual Pose getPose(const cv::Mat &H) const = 0;

protected:
  std::vector<cv::DMatch> matches_;
  std::vector<cv::KeyPoint> srcKeyPoints_;
  std::vector<cv::KeyPoint> dstKeyPoints_;
  float thresh_;
  size_t ransacN_;
};
} // namespace wip
