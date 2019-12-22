add_executable(tester main.cpp TestFeatureExtractor.cpp TestDataset.cpp
                      TestImage.cpp TestRandomSampler.cpp)
target_link_libraries(tester gtest wip stdc++fs)
