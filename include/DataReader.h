#pragma once

#include <opencv2/opencv.hpp>

#include "CameraModel.h"
#include "Image.h"

#include <filesystem>

namespace wip
{
class DataReader
{
public:
  DataReader(const std::filesystem::path& path);
};
} // namespace wip
