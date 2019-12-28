add_library(
  wip
  FeatureExtractor.cpp
  PoseInitializer.cpp
  CameraParameter.cpp
  Image.cpp
  Frame.cpp
  RandomSampler.cpp
  Homography.cpp
  Point.cpp
  Dataset.cpp)

find_package(Boost REQUIRED)
target_include_directories(wip SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(wip SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS}
                                             ${Boost_INCLUDE_DIRS})
target_include_directories(wip SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/third_party/cppglob/include)
target_link_libraries(wip ${OpenCV_LIBS} stdc++fs cppglob)
