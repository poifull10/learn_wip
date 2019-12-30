#include "CameraParameter.h"

#include <boost/optional.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace wip
{
using namespace boost::property_tree;

PinholeCameraParameter::PinholeCameraParameter(
  const std::filesystem::path& fpath)
  : PinholeCameraParameter()
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
    k1_ = pt.get_optional<float>("k1").get();
    k2_ = pt.get_optional<float>("k2").get();
    p1_ = pt.get_optional<float>("p1").get();
    p2_ = pt.get_optional<float>("p2").get();
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
