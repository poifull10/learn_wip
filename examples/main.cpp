#include <boost/program_options.hpp>

#include "Dataset.h"

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
  }
  return 0;
}
