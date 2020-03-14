#include "Dataset.h"

#include <algorithm>
#include <cppglob/glob.hpp>
#include <vector>

namespace wip {
Dataset::Dataset(const std::filesystem::path& path, size_t fileNumLimit)
  : frames_{} {
  namespace fs = std::filesystem;

  std::vector<fs::path> calibs = cppglob::glob(path / "cam.json", true);
  if (calibs.size() > 0) {
    std::cout << "Loading a calibration file: " << calibs[0] << std::endl;
    cameraParameter_ = PinholeCameraParameter(calibs[0]);
  }

  std::vector<fs::path> files = cppglob::glob(path / "*.png", true);
  std::sort(files.begin(), files.end());
  size_t i = 1;
  for (const auto& f : files) {
    std::cout << "Loading an image: " << f << std::endl;
    frames_.emplace_back(std::make_shared<Frame>(f, cameraParameter_));
    if (i == fileNumLimit) { break; }
    i++;
  }
}
} // namespace wip
