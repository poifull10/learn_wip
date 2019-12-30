#include "Image.h"

namespace wip
{
Image load_image(const std::filesystem::path& fpath)
{
  cv::Mat img = cv::imread(fpath.string());
  return Image(std::move(img));
}
} // namespace wip
