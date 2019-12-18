#pragma once

#include <memory>
#include <vector>
#include <array>

namespace wip
{
  constexpr size_t DESCRIPTOR_DIM = 512;

  class KeyPoint
  {

  };

  class Descriptor
  {
    private:
    std::array<bool, DESCRIPTOR_DIM> features_;
  };

  class FeatureExtractorBase
  {
    public:
      FeatureExtractorBase() = default;


    private:
      std::vector<KeyPoint> keyPoints_;
  };
}
