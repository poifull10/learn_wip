#include "Point.h"

namespace wip
{
Point2D operator*(const cv::Mat& mat, const Point2D& point)
{
  const auto ret_ = mat * point.homoMatrix();
  cv::Mat ret;
  cv::convertPointsFromHomogeneous(ret_.t(), ret);
  return Point2D(ret);
}

std::vector<Point2D> operator*(const cv::Mat& mat,
                               const std::vector<Point2D>& points)
{
  std::vector<Point2D> retPoints;
  for (const auto point : points)
  {
    const auto ret_ = mat * point.homoMatrix();
    cv::Mat ret;
    cv::convertPointsFromHomogeneous(ret_.t(), ret);
    retPoints.emplace_back(ret);
  }
  return retPoints;
}

std::vector<Point2D> convertToPoint2D(const std::vector<cv::Point2f>& points)
{
  std::vector<Point2D> retPoints;
  for (const auto point : points)
  {
    retPoints.emplace_back(point);
  }
  return retPoints;
}

} // namespace wip
