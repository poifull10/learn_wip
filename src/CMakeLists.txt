add_library(wip FeatureExtractor.cpp ImageCoordinate.cpp PoseInitializer.cpp
                Dataset.cpp Image.cpp Frame.cpp RandomSampler.cpp)

find_package(Boost REQUIRED)
target_include_directories(wip SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(wip SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS}
                                             ${Boost_INCLUDE_DIRS})

target_link_libraries(wip ${OpenCV_LIBS})
