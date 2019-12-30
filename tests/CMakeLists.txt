add_executable(
  tester
  main.cpp
  TestFeatureExtractor.cpp
  TestCameraParameter.cpp
  TestRandomSampler.cpp
  TestHomography.cpp
  TestPoint.cpp
  TestFundamentalMatrix.cpp
  TestPoseEstimator.cpp)

target_link_libraries(tester gtest wip)
