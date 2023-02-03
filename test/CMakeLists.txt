#cmake_minimum_required(VERSION 3.14)
# as https://github.com/google/googletest/tree/main/googletest

# project(gtest VERSION ${GOOGLETEST_VERSION} LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(kd-search-test kd-search-test.cpp ../src/kd-tree.cpp ../src/kd-search.cpp ../src/helper.cpp) # add this executable
target_link_libraries(kd-search-test gtest)
# add_test(NAME kd-search-test COMMAND )
#add_test(NAME example_test COMMAND kd-search-test)