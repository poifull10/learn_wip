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
  using iterator = typename std::vector<Image>::iterator;
  using const_iterator = typename std::vector<Image>::const_iterator;
  Dataset(const std::filesystem::path& path, size_t fileNumLimit = 0);

  size_t size() const { return images_.size(); }

  iterator begin() { return images_.begin(); }
  iterator end() { return images_.end(); }
  const_iterator begin() const { return images_.begin(); }
  const_iterator end() const { return images_.end(); }

  Image operator[](size_t i) { return images_[i]; }

private:
  std::vector<Image> images_;
  PinholeCameraParameter cameraParameter_;
};
} // namespace wip
