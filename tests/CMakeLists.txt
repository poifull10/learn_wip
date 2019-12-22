add_executable(tester main.cpp TestImageCoordinate.cpp TestFeatureExtractor.cpp
                      TestDataset.cpp TestImage.cpp)
target_link_libraries(tester gtest wip stdc++fs)
