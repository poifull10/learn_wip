#include "CameraParameter.h"

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace wip
{
using namespace boost::property_tree;

PinholeCameraParameter::PinholeCameraParameter(
  const std::filesystem::path& fpath)
  : K_(cv::Size(3, 3), CV_32F), fx_(), fy_(), cx_(), cy_()
{
  ptree pt;
  read_json(fpath.string(), pt);
  if (const auto value = pt.get_optional<float>("fx"))
  {
    // data format fx fy cx cy ...
    fx_ = pt.get_optional<float>("fx").get();
    fy_ = pt.get_optional<float>("fy").get();
    cx_ = pt.get_optional<float>("cx").get();
    cy_ = pt.get_optional<float>("cy").get();
    K_.at<float>(cv::Point(0, 0)) = fx_;
    K_.at<float>(cv::Point(1, 0)) = 0;
    K_.at<float>(cv::Point(2, 0)) = cx_;
    K_.at<float>(cv::Point(0, 1)) = 0;
    K_.at<float>(cv::Point(1, 1)) = fy_;
    K_.at<float>(cv::Point(2, 1)) = cy_;
    K_.at<float>(cv::Point(0, 2)) = 0;
    K_.at<float>(cv::Point(1, 2)) = 0;
    K_.at<float>(cv::Point(2, 2)) = 1;
  }
}

} // namespace wip
