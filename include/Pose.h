#pragma once

#include <array>
#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <tuple>

namespace wip {
class Pose {
public:
  Pose() : quat_{0, 0, 0, 1}, trans_{0, 0, 0} {
  }
  Pose(const std::array<double, 4>& q, const std::array<double, 3>& t)
    : quat_(q), trans_(t) {
  }
  Pose(const Pose& p) : quat_{p.quat_}, trans_{p.trans_} {
  }
  Pose(const cv::Mat& R, const cv::Mat& t) {
    const auto [q_, t_] = toArray(R, t);
    quat_ = q_;
    trans_ = t_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose) {
    os << "quat : rx = " << pose.rx() << ", ry = " << pose.ry()
       << ", rz = " << pose.rz() << ", rw = " << pose.rw() << std::endl;
    os << "trans : x = " << pose.x() << ", y = " << pose.y()
       << ", z = " << pose.z() << std::endl;
    return os;
  }

  std::tuple<std::array<double, 4>, std::array<double, 3>>
  toArray(const cv::Mat& R, const cv::Mat& t) {
    Eigen::Matrix3d m;
    for (size_t iw = 0; iw < 3; iw++) {
      for (size_t ih = 0; ih < 3; ih++) {
        m(ih, iw) = R.at<double>(ih, iw);
      }
    }

    const Eigen::Quaterniond quat(m);
    return {{quat.x(), quat.y(), quat.z(), quat.w()},
            {t.at<double>(cv::Point(0, 0)), t.at<double>(cv::Point(0, 1)),
             t.at<double>(cv::Point(0, 2))}};
  }

  std::array<double, 4> quat() const {
    return quat_;
  }
  std::array<double, 3> trans() const {
    return trans_;
  }

  double rx() const {
    return quat_[0];
  }
  double ry() const {
    return quat_[1];
  }
  double rz() const {
    return quat_[2];
  }
  double rw() const {
    return quat_[3];
  }
  double x() const {
    return trans_[0];
  }
  double y() const {
    return trans_[1];
  }
  double z() const {
    return trans_[2];
  }

  Pose inverse() const {
    const Eigen::Quaterniond quat(rw(), rx(), ry(), rz());
    Eigen::Matrix3d m(quat);
    const Eigen::Quaterniond quat_inv(m.transpose());
    const Eigen::Vector3d t = -m.transpose() * Eigen::Vector3d(x(), y(), z());

    return Pose(std::array<double, 4>{quat_inv.x(), quat_inv.y(), quat_inv.z(),
                                      quat_inv.w()},
                std::array<double, 3>{t.x(), t.y(), t.z()});
  }

  double norm() const {
    return std::sqrt(x() * x() + y() * y() + z() * z());
  }

  Pose operator/(double v) const {
    return Pose(quat(), {x() / v, y() / v, z() / v});
  }

private:
  std::array<double, 4> quat_;
  std::array<double, 3> trans_;
};

} // namespace wip
