#pragma once
#include <opencv2/opencv.hpp>

#include <filesystem>
#include <string>
#include <vector>

namespace wip
{

class PinholeCameraParameter
{
public:
  PinholeCameraParameter() = default;
  PinholeCameraParameter(const PinholeCameraParameter& pcp) = default;
  PinholeCameraParameter(const std::filesystem::path& fpath);

  PinholeCameraParameter& operator=(const PinholeCameraParameter& pcp) =
    default;

  cv::Mat K() const { return K_; }
  std::vector<float> dist() const { return dist_; }

private:
  cv::Mat K_;
  std::vector<float> dist_;
  float fx_, fy_, cx_, cy_;
};

} // namespace wip