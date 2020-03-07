#include "FeatureExtractor.h"

namespace wip
{

std::pair<std::vector<cv::KeyPoint>, cv::Mat> FeatureExtractor::operator()(
  const Image& image) const
{
  const auto detector = cv::ORB::create(featureNum_); //(150, 1.25f, 30);
  cv::Mat description;
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(image.data(), keypoints);
  detector->compute(image.data(), keypoints, description);
  return {keypoints, description};
}

} // namespace wip
