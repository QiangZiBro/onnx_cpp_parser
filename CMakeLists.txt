######################################################################
# @author      : QiangZiBro (qiangzibro@gmail.com)
# @file        : CMakeLists
# @created     : 星期三  3 15, 2023 21:33:01 CST
######################################################################

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ParseOnnx LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(/opt/homebrew/include)
find_library(LIBPROTOBUF NAMES protobuf PATHS /opt/homebrew/lib/)

add_executable(main main.cc onnx.pb.cc)
target_link_libraries(main ${LIBPROTOBUF})
