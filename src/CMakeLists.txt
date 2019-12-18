
add_library(wip FeatureExtractor.cpp ImageCoordinate.cpp)
target_include_directories(wip SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include)

