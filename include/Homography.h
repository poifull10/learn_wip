#pragma once

#include <opencv2/opencv.hpp>

#include "Point.h"

#include <utility>
#include <vector>

namespace wip
{
class HomographyEstimator
{
public:
  HomographyEstimator(const std::vector<cv::DMatch> &matches,
                      const std::vector<cv::KeyPoint> &srcKeyPoints,
                      const std::vector<cv::KeyPoint> &dstKeyPoints,
                      size_t ransacN = 30)
    : matches_(matches)
    , srcKeyPoints_(srcKeyPoints)
    , dstKeyPoints_(dstKeyPoints)
    , ransacN_(ransacN)
    , thresh_(2.44765)
  {
  }

  HomographyEstimator(size_t ransacN = 30)
    : matches_()
    , srcKeyPoints_()
    , dstKeyPoints_()
    , ransacN_(ransacN)
    , thresh_(2.44765)
  {
  }

  std::pair<float, cv::Mat> estimate();

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const;

  float evaluate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                 const std::vector<cv::Point2f> &dstPoints) const;

private:
  float evalFunc(const float val) const;

  std::vector<cv::DMatch> matches_;
  std::vector<cv::KeyPoint> srcKeyPoints_;
  std::vector<cv::KeyPoint> dstKeyPoints_;
  float thresh_;
  size_t ransacN_;
};
} // namespace wip
