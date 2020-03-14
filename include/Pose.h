#pragma once

#include <array>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tuple>

namespace wip {
class Pose {
public:
  Pose() : quat_{0, 0, 0, 1}, trans_{0, 0, 0} {}
  Pose(const Pose& p) : quat_{p.quat_}, trans_{p.trans_} {}
  Pose(const cv::Mat& R, const cv::Mat& t) {
    const auto [q, t_] = toArray(R, t);
    quat_              = q;
    trans_             = t_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose) {
    os << "quat : rx = " << pose.rx() << ", ry = " << pose.ry()
       << ", rz = " << pose.rz() << ", rw = " << pose.rw() << std::endl;
    os << "trans : x = " << pose.x() << ", y = " << pose.y()
       << ", z = " << pose.z() << std::endl;
    return os;
  }

  std::tuple<std::array<float, 4>, std::array<float, 3>>
  toArray(const cv::Mat& R, const cv::Mat& t) {
    Eigen::Matrix3f m;
    for (size_t iw = 0; iw < 3; iw++) {
      for (size_t ih = 0; ih < 3; ih++) { m(ih, iw) = R.at<float>(ih, iw); }
    }

    const Eigen::Quaternionf quat(m);
    return {{quat.x(), quat.y(), quat.z(), quat.w()},
            {t.at<float>(0, 0), t.at<float>(1, 0), t.at<float>(2, 0)}};
  }

  std::array<float, 4> quat() const { return quat_; }
  std::array<float, 3> trans() const { return trans_; }

  float rx() const { return quat_[0]; }
  float ry() const { return quat_[1]; }
  float rz() const { return quat_[2]; }
  float rw() const { return quat_[3]; }
  float x() const { return trans_[0]; }
  float y() const { return trans_[1]; }
  float z() const { return trans_[2]; }

private:
  std::array<float, 4> quat_;
  std::array<float, 3> trans_;
};
} // namespace wip
