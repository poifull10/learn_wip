#pragma once

#include <opencv2/opencv.hpp>

#include "CameraParameter.h"
#include "Frame.h"
#include "Image.h"

#include <filesystem>
#include <memory>
#include <vector>

namespace wip {

class Dataset {
public:
  using iterator = typename std::vector<std::shared_ptr<Frame>>::iterator;
  using const_iterator =
    typename std::vector<std::shared_ptr<Frame>>::const_iterator;
  Dataset(const std::filesystem::path& path, size_t fileNumLimit = 0);

  size_t size() const { return frames_.size(); }

  iterator begin() { return frames_.begin(); }
  iterator end() { return frames_.end(); }
  const_iterator begin() const { return frames_.begin(); }
  const_iterator end() const { return frames_.end(); }

  std::shared_ptr<Frame> operator[](size_t i) { return frames_[i]; }

private:
  std::vector<std::shared_ptr<Frame>> frames_;
  PinholeCameraParameter cameraParameter_;
};

} // namespace wip
