#pragma once

#include <opencv2/opencv.hpp>

#include <array>
#include <iostream>

namespace wip
{
class Pose
{
public:
  Pose() : quat_{0, 0, 0, 1}, trans_{0, 0, 0} {}
  Pose(const Pose& p) : quat_{p.quat_}, trans_{p.trans_} {}

  friend std::ostream& operator<<(std::ostream& os, const Pose& pose)
  {
    const auto quat_ = pose.quat();
    const auto trans_ = pose.trans();
    os << "quat : " << quat_[0] << ", " << quat_[1] << ", " << quat_[2] << ", "
       << quat_[3] << std::endl;
    os << "trans : " << trans_[0] << ", " << trans_[1] << ", " << trans_[2]
       << std::endl;
    return os;
  }

  std::array<float, 4> quat() const { return quat_; }
  std::array<float, 3> trans() const { return trans_; }

private:
  std::array<float, 4> quat_;
  std::array<float, 3> trans_;
};
} // namespace wip
