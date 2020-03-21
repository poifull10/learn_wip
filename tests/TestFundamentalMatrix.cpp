#include <gtest/gtest.h>

#include "FundamentalMatrix.h"

TEST(FundamentalMatrix, test_calculate) {
  wip::FundamentalMatrixEstimator fme;
  std::vector<cv::Point2d> src;
  src.emplace_back(0.54080616, 0.78067211);
  src.emplace_back(0.05286922, 0.07238643);
  src.emplace_back(0.28100833, 0.87153334);
  src.emplace_back(0.81365147, 0.51020043);
  src.emplace_back(0.62895895, 0.4381112);
  src.emplace_back(0.11672991, 0.48398556);
  src.emplace_back(0.45910073, 0.75345235);
  src.emplace_back(0.70279012, 0.59405252);
  std::vector<cv::Point2d> dst;
  dst.emplace_back(0.99879817, 0.19333665);
  dst.emplace_back(0.0462407, 0.65652249);
  dst.emplace_back(0.31125151, 0.89136524);
  dst.emplace_back(0.04204784, 0.30899411);
  dst.emplace_back(0.89847986, 0.83229613);
  dst.emplace_back(0.11090126, 0.72823089);
  dst.emplace_back(0.64419448, 0.28517263);
  dst.emplace_back(0.55505818, 0.74641622);

  const auto F = fme.calculate(src, dst);

  cv::Mat srcMat = cv::Mat::zeros(8, 3, CV_64F);
  cv::Mat dstMat = cv::Mat::zeros(8, 3, CV_64F);

  for (size_t i = 0; i < 8; i++) {
    srcMat.at<double>(i, 0) = src[i].x;
    srcMat.at<double>(i, 1) = src[i].y;
    srcMat.at<double>(i, 2) = 1;
    dstMat.at<double>(i, 0) = dst[i].x;
    dstMat.at<double>(i, 1) = dst[i].y;
    dstMat.at<double>(i, 2) = 1;
  }

  // std::cout << F << std::endl;

  // std::cout << srcMat << std::endl;
  // std::cout << "F : " << F.type() << std::endl;
  // std::cout << "dstMat : " << dstMat.type() << std::endl;
  // std::cout << "ch : " << dstMat.channels() << std::endl;
  // std::cout << "dstMat.t : " << dstMat.t().type() << std::endl;
  // std::cout << cv::Mat(F * dstMat.t()) << std::endl;

  // EXPECT_NEAR(F.at<double>(cv::Point(0, 0)), 1.236310675488192, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(1, 0)), -0.6012650992821675, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(2, 0)), -0.2489597912028044, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(0, 1)), 0.2338248968427974, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(1, 1)), 1.690001510064117, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(2, 1)), -1.531029942127715, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(0, 2)), -0.5465231267368235, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(1, 2)), -0.8159243904447714, 1e-3);
  // EXPECT_NEAR(F.at<double>(cv::Point(2, 2)), 1, 1e-3);
}

TEST(FundamentalMatrix, test_evaluate) {
  wip::FundamentalMatrixEstimator fme;
  std::vector<cv::Point2d> src;
  src.emplace_back(54.080616, 78.067211);
  src.emplace_back(5.286922, 7.238643);
  src.emplace_back(28.100833, 87.153334);
  src.emplace_back(81.365147, 51.020043);
  src.emplace_back(62.895895, 43.81112);
  src.emplace_back(11.672991, 48.398556);
  src.emplace_back(45.910073, 75.345235);
  src.emplace_back(70.279012, 59.405252);
  std::vector<cv::Point2d> dst;
  dst.emplace_back(99.879817, 19.333665);
  dst.emplace_back(4.62407, 65.652249);
  dst.emplace_back(31.125151, 89.136524);
  dst.emplace_back(4.204784, 30.899411);
  dst.emplace_back(89.847986, 83.229613);
  dst.emplace_back(11.090126, 72.823089);
  dst.emplace_back(64.419448, 28.517263);
  dst.emplace_back(55.505818, 74.641622);

  const auto F = fme.calculate(src, dst);
  const auto [score, _] = fme.evaluate(F, src, dst);

  EXPECT_GT(score, 5.99f * 16 / 2);
}

TEST(FundamentalMatrix, test_calc_pose) {
  wip::FundamentalMatrixEstimator fme;
  std::vector<cv::Point2d> src;
  src.emplace_back(770, 449);
  src.emplace_back(773, 824);
  src.emplace_back(1147, 823);
  src.emplace_back(1150, 449);
  src.emplace_back(294, 682);
  src.emplace_back(444, 1019);
  src.emplace_back(1594, 603);
  src.emplace_back(1581, 102);
  std::vector<cv::Point2d> dst;
  dst.emplace_back(767, 449);
  dst.emplace_back(769, 823);
  dst.emplace_back(1143, 824);
  dst.emplace_back(1145, 449);
  dst.emplace_back(293, 682);
  dst.emplace_back(440, 1019);
  dst.emplace_back(1593, 605);
  dst.emplace_back(1580, 103);

  cv::Mat K = cv::Mat::eye(3, 3, CV_64F);
  K.at<double>(cv::Point(0, 0)) = 2666.666666666667;
  K.at<double>(cv::Point(1, 1)) = 2250.0;
  K.at<double>(cv::Point(2, 0)) = 960.0;
  K.at<double>(cv::Point(2, 1)) = 540.0;

  const auto F = fme.calculate(src, dst);
  const auto pose = fme.calcPose(F, K);
  const auto normalized_inv_pose = pose.inverse() / pose.inverse().norm();
  std::cout << normalized_inv_pose << std::endl;
  std::cout << pose << std::endl;
  EXPECT_GT(normalized_inv_pose.x(), 0.9);
  EXPECT_GT(normalized_inv_pose.rw(), 0.99);
}
