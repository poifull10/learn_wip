#include "FeatureExtractor.h"

namespace wip {

std::tuple<std::vector<cv::KeyPoint>, cv::Mat>
FeatureExtractor::operator()(const Image& image) const {
  size_t gridWidth  = image.width() / gridX - 1;
  size_t gridHeight = image.height() / gridY - 1;

  const auto detector =
    cv::ORB::create(featureNum_ / (gridX * gridY), 1.2F, 4, 11);
  cv::Mat description;
  std::vector<cv::KeyPoint> keypoints;
  for (size_t ih = 0; ih < gridY; ih++) {
    for (size_t iw = 0; iw < gridX; iw++) {
      const Image img =
        image.trim(iw * gridWidth, ih * gridHeight, gridWidth, gridHeight);
      std::vector<cv::KeyPoint> kpt;
      cv::Mat desc;
      detector->detect(img.data(), kpt);
      detector->compute(img.data(), kpt, desc);
      for (size_t ik = 0; ik < kpt.size(); ik++) {
        kpt[ik].pt += cv::Point2f(iw * gridWidth, ih * gridHeight);
      }
      keypoints.insert(keypoints.end(), kpt.begin(), kpt.end());
      if (description.cols == 0) {
        description = desc;
      } else if (description.cols == desc.cols) {
        cv::vconcat(std::vector<cv::Mat>{description, desc}, description);
      }
    }
  }

  return {keypoints, description};
}

} // namespace wip
