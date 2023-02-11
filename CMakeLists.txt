CMAKE_MINIMUM_REQUIRED(VERSION 3.2)
project("KD-tree" VERSION 0.2.0 LANGUAGES "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")

SET (CMAKE_CXX_FLAGS "-O2")
# include_directories("${CMAKE_SOURCE_DIR}/src")

# adding subdirectories 
# add_subdirectory(src)
# add_subdirectory(test)
add_subdirectory(test) # add googletest subdirectory


add_executable(main src/main.cpp src/kd-tree.cpp src/kd-search.cpp src/helper.cpp)


