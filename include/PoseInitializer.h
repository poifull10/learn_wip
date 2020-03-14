#pragma once
#include <opencv2/opencv.hpp>
#include "FeatureExtractor.h"
#include "Frame.h"
#include "Image.h"
#include "Pose.h"
#include <optional>

namespace wip {
class PoseInitializer {
public:
  PoseInitializer() : featureExtractor_(), ransac_n_(100) {}
  std::optional<Pose> operator()(Frame &src, Frame &dst) const;

private:
  FeatureExtractor featureExtractor_;
  size_t ransac_n_;
};
} // namespace wip
