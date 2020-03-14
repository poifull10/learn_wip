#include <boost/format.hpp>
#include <boost/program_options.hpp>
#include <opencv2/opencv.hpp>
#include <string>

#include "Dataset.h"
#include "FeatureExtractor.h"
#include "PoseInitializer.h"

int main(int argc, char** argv) {
  namespace bopt = boost::program_options;
  bopt::options_description opt("Options");
  opt.add_options()("help,h", "show help")(
    "dir,D", bopt::value<std::string>(), "data dir")("debug,d",
                                                     "debug mode, dump files");

  bopt::variables_map vm;

  try {
    bopt::store(bopt::parse_command_line(argc, argv, opt), vm);
  } catch (const bopt::error_with_option_name& e) {
    std::cout << e.what() << std::endl;
  }
  bopt::notify(vm);

  if (vm.count("help")) {
    std::cout << opt << std::endl;
    return 0;
  }

  if (vm.count("dir")) {
    const auto dataDir = vm["dir"].as<std::string>();
    wip::Dataset dataset(dataDir, 55);
    std::cout << dataset.size() << std::endl;

    wip::FeatureExtractor fe;
    size_t i = 0;
    if (vm.count("debug")) {
      // draw keypoints
      for (const auto& frame : dataset) {
        const auto [keypoints, desc] = fe(frame->image().data());

        cv::Mat img = frame->image().data();
        cv::drawKeypoints(img, keypoints, img, cv::Scalar(0, 255, 0));
        const std::string s = (boost::format("%04d.png") % (i + 1)).str();
        std::cout << "Writing: " << s << std::endl;
        cv::imwrite(s, img);
        i++;
      }
    }

    // estimate camera poses
    for (size_t i = 0; i < 1; i++) {
      wip::PoseInitializer pi;
      const auto pose = pi(*dataset[i], *dataset[i + 50]);
      if (pose) { std::cout << *pose << std::endl; }
    }
  }
  return 0;
}
