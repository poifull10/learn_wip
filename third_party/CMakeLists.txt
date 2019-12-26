add_subdirectory(gtest)

add_library(wip_eigen INTERFACE)
target_include_directories(wip_eigen SYSTEM INTERFACE eigen/)
