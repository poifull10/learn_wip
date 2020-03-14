#pragma once
#include <opencv2/opencv.hpp>

#include <filesystem>
#include <string>
#include <tuple>
#include <vector>

namespace wip {

class PinholeCameraParameter {
public:
  PinholeCameraParameter()
    : K_(std::move(cv::Mat::eye(3, 3, CV_32F))), fx_(), fy_(), cx_(), cy_(),
      k1_(), k2_(), p1_(), p2_() {}
  PinholeCameraParameter(const PinholeCameraParameter& pcp) = default;
  PinholeCameraParameter(const std::filesystem::path& fpath);

  PinholeCameraParameter&
  operator=(const PinholeCameraParameter& pcp) = default;

  cv::Mat K() const {
    return (cv::Mat_<float>(3, 3) << fx_, 0, cx_, 0, fy_, cy_, 0, 0, 1);
  }
  std::tuple<float, float, float, float> distCoeff() const {
    return {k1_, k2_, p1_, p2_};
  }

private:
  cv::Mat K_;
  float p1_, p2_, k1_, k2_;
  float fx_, fy_, cx_, cy_;
};

} // namespace wip