CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project("KD-tree" VERSION 0.2.0 LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include_directories("${CMAKE_SOURCE_DIR}/src")

# adding subdirectories 
# add_subdirectory(src)
# add_subdirectory(test)


add_executable(main src/main.cpp src/kd-tree.cpp src/kd-search.cpp)
