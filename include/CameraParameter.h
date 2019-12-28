#pragma once
#include <opencv2/opencv.hpp>

#include <filesystem>
#include <string>
#include <tuple>
#include <vector>

namespace wip
{

class PinholeCameraParameter
{
public:
  PinholeCameraParameter()
    : K_(cv::Size(3, 3), CV_32F)
    , fx_()
    , fy_()
    , cx_()
    , cy_()
    , k1_()
    , k2_()
    , p1_()
    , p2_()
  {
  }
  PinholeCameraParameter(const PinholeCameraParameter& pcp) = default;
  PinholeCameraParameter(const std::filesystem::path& fpath);

  PinholeCameraParameter& operator=(const PinholeCameraParameter& pcp) =
    default;

  cv::Mat K() const { return K_; }
  std::tuple<float, float, float, float> distCoeff() const { return {k1_, k2_, p1_, p2_}; }

private:
  cv::Mat K_;
  float p1_, p2_, k1_, k2_;
  float fx_, fy_, cx_, cy_;
};

} // namespace wip