#include "Dataset.h"

#include <cppglob/glob.hpp>

#include <algorithm>
#include <vector>

namespace wip
{
Dataset::Dataset(const std::filesystem::path& path, size_t fileNumLimit)
  : images_{}
{
  namespace fs = std::filesystem;

  std::vector<fs::path> files = cppglob::glob(path / "cam0/*.png", true);
  std::sort(files.begin(), files.end());
  size_t i = 1;
  for (const auto& f : files)
  {
    std::cout << "Loading an image: " << f << std::endl;
    images_.push_back(load_image(f));
    if (i == fileNumLimit)
    {
      break;
    }
    i++;
  }

  std::vector<fs::path> calibs = cppglob::glob(path / "cam0.json", true);
  if (calibs.size() > 0)
  {
    std::cout << "Loading a calibration file: " << calibs[0] << std::endl;
    cameraParameter_ = PinholeCameraParameter(calibs[0]);
  }
}
} // namespace wip
