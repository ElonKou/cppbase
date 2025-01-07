cmake_minimum_required(VERSION 3.10)
project(short_str)

# 添加Google Test库
enable_testing()
find_package(GTest REQUIRED)
include_directories(
    ${GTEST_INCLUDE_DIRS}
    ../../include
)

# 添加可执行文件
add_executable(short_str main.cc)

# 链接Google Test库
target_link_libraries(short_str ${GTEST_LIBRARIES} pthread)

# 添加测试
add_test(NAME MyTests COMMAND short_str)
