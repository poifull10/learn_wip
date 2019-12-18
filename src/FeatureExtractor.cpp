#include "FeatureExtractor.h"

namespace wip
{

std::pair<std::vector<cv::KeyPoint>, cv::Mat> FeatureExtractor::operator()(
  const cv::Mat& image) const
{
  const auto detector = cv::ORB::create();
  cv::Mat description;
  std::vector<cv::KeyPoint> keypoints;
  detector->detect(image, keypoints);
  detector->compute(image, keypoints, description);
  return {keypoints, description};
}

} // namespace wip