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
  PoseInitializer() : featureExtractor_(), ransac_n_(30) {}
  Pose operator()(const Image &src, const Image &dst) const;

private:
  FeatureExtractor featureExtractor_;
  size_t ransac_n_;
};
} // namespace wip
