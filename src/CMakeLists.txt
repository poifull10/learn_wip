add_library(wip FeatureExtractor.cpp ImageCoordinate.cpp)

target_include_directories(wip SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(wip SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS})

target_link_libraries(wip ${OpenCV_LIBS})
