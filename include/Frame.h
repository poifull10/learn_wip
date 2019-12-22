#pragma once

#include <memory>

#include <Image.h>
#include <Pose.h>

namespace wip

{

class Frame
{
public:
  Frame(std::shared_ptr<Image> img) : image_(img), pose_() {}

private:
  std::shared_ptr<Image> image_;
  Pose pose_;
};
} // namespace wip