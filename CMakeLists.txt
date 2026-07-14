cmake_minimum_required(VERSION 3.10)
project(CV_Auto)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "src/**/*.cpp" "src/*.cpp")

add_executable(CV_Auto ${SOURCES}
        src/model/CVFilter.cpp)

include_directories(src)

