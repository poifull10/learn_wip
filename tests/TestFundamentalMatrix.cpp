#include <gtest/gtest.h>

#include "FundamentalMatrix.h"

TEST(FundamentalMatrix, test_calc_fundamental_matrix)
{
  wip::FundamentalMatrixEstimator fme;
  std::vector<cv::Point2f> src;
  src.emplace_back(0.54080616, 0.78067211);
  src.emplace_back(0.05286922, 0.07238643);
  src.emplace_back(0.28100833, 0.87153334);
  src.emplace_back(0.81365147, 0.51020043);
  src.emplace_back(0.62895895, 0.4381112);
  src.emplace_back(0.11672991, 0.48398556);
  src.emplace_back(0.45910073, 0.75345235);
  src.emplace_back(0.70279012, 0.59405252);
  std::vector<cv::Point2f> dst;
  dst.emplace_back(0.99879817, 0.19333665);
  dst.emplace_back(0.0462407, 0.65652249);
  dst.emplace_back(0.31125151, 0.89136524);
  dst.emplace_back(0.04204784, 0.30899411);
  dst.emplace_back(0.89847986, 0.83229613);
  dst.emplace_back(0.11090126, 0.72823089);
  dst.emplace_back(0.64419448, 0.28517263);
  dst.emplace_back(0.55505818, 0.74641622);

  const auto F = fme.calculate(src, dst);

  EXPECT_NEAR(F.at<double>(cv::Point(0, 0)), 1.236310675488192, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(1, 0)), -0.6012650992821675, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(2, 0)), -0.2489597912028044, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(0, 1)), 0.2338248968427974, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(1, 1)), 1.690001510064117, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(2, 1)), -1.531029942127715, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(0, 2)), -0.5465231267368235, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(1, 2)), -0.8159243904447714, 1e-3);
  EXPECT_NEAR(F.at<double>(cv::Point(2, 2)), 1, 1e-3);
}
