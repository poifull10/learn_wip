#pragma once

#include <Image.h>
#include <opencv2/opencv.hpp>
#include <tuple>
#include <vector>
namespace wip {
class FeatureExtractor {
public:
  FeatureExtractor() : featureNum_(320), gridX(16), gridY(4) {}

  std::tuple<std::vector<cv::KeyPoint>, cv::Mat>
  operator()(const Image& image) const;

  size_t featureNum() const { return featureNum_; }

private:
  size_t featureNum_;
  size_t gridX, gridY;
};
} // namespace wip
