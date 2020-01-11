#pragma once

#include <opencv2/opencv.hpp>

#include <vector>

namespace wip
{
std::pair<std::vector<cv::Point2f>, std::vector<cv::Point2f>> getMatchedPoints(
  const std::vector<cv::DMatch>& matches, const std::vector<cv::KeyPoint>& src,
  const std::vector<cv::KeyPoint>& dst)
{
  std::vector<cv::Point2f> matchedSrc, matchedDst;
  for (const auto& match : matches)
  {
    matchedSrc.push_back(src[match.trainIdx].pt);
    matchedDst.push_back(dst[match.queryIdx].pt);
  }

  return {matchedSrc, matchedDst};
}
} // namespace wip
