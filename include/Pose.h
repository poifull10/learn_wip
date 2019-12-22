#pragma once

#include <opencv2/opencv.hpp>

#include <array>

namespace wip
{
class Pose
{
public:
  Pose() : quat_{0, 0, 0, 1}, trans_{0, 0, 0} {}
  Pose(const Pose& p) : quat_{p.quat_}, trans_{p.trans_} {}

private:
  std::array<float, 4> quat_;
  std::array<float, 3> trans_;
};
} // namespace wip
