#pragma once
#include <opencv2/opencv.hpp>

#include "FeatureExtractor.h"
#include "Image.h"
#include "Pose.h"

namespace wip
{
class PoseInitializer
{
public:
  PoseInitializer() : featureExtractor_() {}
  Pose operator()(const Image &src, const Image &dst) const;

private:
  FeatureExtractor featureExtractor_;
};
} // namespace wip