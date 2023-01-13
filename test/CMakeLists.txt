include_directories(../src)

add_executable(test test-runner.cpp kd-search.test.cpp kd-tree.test.cpp)
target_link_libraries(test kd-tree)