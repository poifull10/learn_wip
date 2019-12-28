#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <opencv2/opencv.hpp>

#include "Dataset.h"
#include "FeatureExtractor.h"

#include <string>

int main(int argc, char** argv)
{
  namespace bopt = boost::program_options;
  bopt::options_description opt("Options");
  opt.add_options()("help,h", "show help")("dir,d", bopt::value<std::string>(),
                                           "data dir");

  bopt::variables_map vm;

  try
  {
    bopt::store(bopt::parse_command_line(argc, argv, opt), vm);
  }
  catch (const bopt::error_with_option_name& e)
  {
    std::cout << e.what() << std::endl;
  }
  bopt::notify(vm);

  if (vm.count("help"))
  {
    std::cout << opt << std::endl;
    return 0;
  }

  if (vm.count("dir"))
  {
    const auto dataDir = vm["dir"].as<std::string>();
    wip::Dataset dataset(dataDir);
    std::cout << dataset.size() << std::endl;

    wip::FeatureExtractor fe;
    size_t i = 0;
    for (const auto& image : dataset){
      const auto [keypoints, desc] = fe(image.data());
      cv::Mat img = image.data();
      img.convertTo(img, CV_8UC3);
      cv::drawKeypoints(img, keypoints, img, cv::Scalar(0, 255, 0));
      const std::string s = (boost::format("%04d.png") % i).str();
      std::cout << s << std::endl;
      cv::imwrite(s, img);
      i++;
    }

  }
  return 0;
}
