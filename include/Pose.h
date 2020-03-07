#pragma once

#include <array>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tuple>

namespace wip
{
class Pose
{
public:
  Pose() : quat_{0, 0, 0, 1}, trans_{0, 0, 0} {}
  Pose(const Pose& p) : quat_{p.quat_}, trans_{p.trans_} {}
  Pose(const cv::Mat& R, const cv::Mat& t)
  {
    const auto [q, t_] = toArray(R, t);
    quat_ = q;
    trans_ = t_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose)
  {
    const auto quat_ = pose.quat();
    const auto trans_ = pose.trans();
    os << "quat : rx = " << quat_[0] << ", ry = " << quat_[1]
       << ", rz = " << quat_[2] << ", rw = " << quat_[3] << std::endl;
    os << "trans : x = " << trans_[0] << ", y = " << trans_[1]
       << ", z = " << trans_[2] << std::endl;
    return os;
  }

  std::tuple<std::array<float, 4>, std::array<float, 3>> toArray(
    const cv::Mat& R, const cv::Mat& t)
  {
    Eigen::Matrix3f m;
    m(0, 0) = R.at<float>(0, 0);
    m(1, 0) = R.at<float>(1, 0);
    m(2, 0) = R.at<float>(2, 0);
    m(0, 1) = R.at<float>(0, 1);
    m(1, 1) = R.at<float>(1, 1);
    m(2, 1) = R.at<float>(2, 1);
    m(0, 2) = R.at<float>(0, 2);
    m(1, 2) = R.at<float>(1, 2);
    m(2, 2) = R.at<float>(2, 2);

    Eigen::Quaternionf quat(m);
    return {{quat.x(), quat.y(), quat.z(), quat.w()},
            {t.at<float>(0, 0), t.at<float>(1, 0), t.at<float>(2, 0)}};
  }

  std::array<float, 4> quat() const { return quat_; }
  std::array<float, 3> trans() const { return trans_; }

private:
  std::array<float, 4> quat_;
  std::array<float, 3> trans_;
};
} // namespace wip
