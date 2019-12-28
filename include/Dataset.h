#pragma once

#include <opencv2/opencv.hpp>

#include "CameraParameter.h"
#include "Image.h"

#include <filesystem>
#include <vector>

namespace wip
{

class Dataset
{
public:
  Dataset(const std::filesystem::path& path);

  size_t size() const { return images_.size(); }

private:
  std::vector<Image> images_;
  PinholeCameraParameter cameraParameter_;
};
} // namespace wip
