#include "Image.h"

namespace wip {
Image load_image(const std::filesystem::path& fpath) {
  cv::Mat img = cv::imread(fpath.string());
  return Image(std::move(img));
}

Image Image::trim(size_t x, size_t y, size_t w, size_t h) const {
  return Image(data()(cv::Range(y, y + h), cv::Range(x, x + w)));
}
} // namespace wip
