#pragma once

#include <opencv2/opencv.hpp>

#include <array>
#include <memory>
#include <utility>
#include <vector>

#include <Image.h>
namespace wip
{
class FeatureExtractor
{
public:
  FeatureExtractor(int FASTThresh = 30) : FASTThresh_(FASTThresh) {}

  std::pair<std::vector<cv::KeyPoint>, cv::Mat> operator()(
    const Image& image) const;

private:
  int FASTThresh_;
};
} // namespace wip
