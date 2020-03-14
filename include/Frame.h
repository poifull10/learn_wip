#pragma once

#include <memory>

#include <CameraParameter.h>
#include <Image.h>
#include <Pose.h>

namespace wip

{

class Frame {
public:
  Frame(const std::filesystem::path& path,
        const PinholeCameraParameter& cameraParameter)
    : image_(std::move(cv::imread(path.string()))), pose_(),
      cameraParameter_(cameraParameter) {}

  Frame(const Image& img, const PinholeCameraParameter& cameraParameter)
    : image_(img), pose_(), cameraParameter_(cameraParameter) {}

  Frame(Image&& img, const PinholeCameraParameter& cameraParameter)
    : image_(std::move(img)), pose_(), cameraParameter_(cameraParameter) {}

  Image image() const { return image_; }

  Image image_;
  Pose pose_;
  PinholeCameraParameter cameraParameter_;
};
} // namespace wip