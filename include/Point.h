#pragma once

#include <opencv2/opencv.hpp>

#include <optional>
#include <vector>

namespace wip {
class Point2D {
public:
  Point2D() = delete;
  Point2D(const cv::Point2d& point)
    : point_(cv::Mat(point).reshape(1, 1)), point3_() {
    cv::convertPointsToHomogeneous(point_, point3_);
    point3_ = point3_.reshape(1, 1);
  }
  Point2D(const double x, const double y) : Point2D(cv::Point2d(x, y)) {}
  Point2D(const cv::Mat& point) : point3_() {
    point_ = point.reshape(1, 1);
    assert(point_.rows == 1);
    assert(point_.cols == 2);
    cv::convertPointsToHomogeneous(point_, point3_);
    point3_ = point3_.reshape(1, 1);
  }

  cv::Mat matrix() const { return point_.t(); }
  cv::Mat homoMatrix() const { return point3_.t(); }
  cv::Point2d point() const { return cv::Point2d(point_); }

  double x() const { return point_.at<double>(cv::Point(0, 0)); }
  double y() const { return point_.at<double>(cv::Point(1, 0)); }

private:
  cv::Mat point_;
  cv::Mat point3_;
};

Point2D operator*(const cv::Mat& mat, const Point2D& point);
Point2D operator-(const Point2D& lhs, const Point2D& rhs);

std::vector<Point2D> operator*(const cv::Mat& mat,
                               const std::vector<Point2D>& points);

std::vector<Point2D> convertToPoint2D(const std::vector<cv::Point2d>& points);

} // namespace wip
