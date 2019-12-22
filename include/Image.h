#pragma once

#include <opencv2/opencv.hpp>

#include <filesystem>

namespace wip
{

class Image
{
public:
  Image(cv::Mat&& img) : data_(std::move(img)){};
  Image() : data_(){};

  Image(const Image&) = delete;
  Image& operator=(const Image& image) = delete;

  cv::Mat data() const { return data_; }
  size_t width() const { return data_.cols; }
  size_t height() const { return data_.rows; }

private:
  cv::Mat data_;
};

Image load_image(const std::filesystem::path& fpath);

} // namespace wip