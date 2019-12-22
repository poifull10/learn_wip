#include <gtest/gtest.h>

#include "Image.h"

TEST(Image, test_load)
{
  const auto image = wip::load_image("../tests/lenna.png");
  EXPECT_EQ(image.width(), 512);
  EXPECT_EQ(image.height(), 480);
}