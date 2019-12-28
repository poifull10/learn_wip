#include "Dataset.h"

#include <cppglob/glob.hpp>

#include <algorithm>
#include <vector>


namespace wip
{
Dataset::Dataset(const std::filesystem::path& path) : images_ {}
{
  namespace fs = std::filesystem;

  std::vector<fs::path> files = cppglob::glob(path / "cam0/*.png", true);
  std::sort(files.begin(), files.end());
  for (const auto& f : files) {
    std::cout << "Loading: " << f << std::endl;
    images_.push_back(load_image(f));
  }

  std::vector<fs::path> calibs = cppglob::glob(path / "cam0.json", true);
  if (calibs.size() > 0){
    std::cout << "Loading: " << calibs[0] << std::endl;
    cameraParameter_ = PinholeCameraParameter(calibs[0]);
  }
}
} // namespace wip
