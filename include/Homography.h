#pragma once

#include <opencv2/opencv.hpp>

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
  {
  }

  HomographyEstimator(size_t ransacN = 30)
    : matches_(), srcKeyPoints_(), dstKeyPoints_(), ransacN_(ransacN)
  {
  }

  std::pair<float, cv::Mat> estimate();

  /**
   *  @return double matrix
   */
  cv::Mat calculate(const std::vector<cv::Point2f> &srcPoints,
                    const std::vector<cv::Point2f> &dstPoints) const;

private:
  size_t ransacN_;
  float evalueate(const cv::Mat &H, std::vector<cv::Point2f> &srcPoints,
                  const std::vector<cv::Point2f> &dstPoints) const;

  std::vector<cv::DMatch> matches_;
  std::vector<cv::KeyPoint> srcKeyPoints_;
  std::vector<cv::KeyPoint> dstKeyPoints_;
};
} // namespace wip
