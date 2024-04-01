
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(NLOHMAN_JSON_ CXX)

set(NLO_JSON_DIR "E:/MyCode/third_party/json/include")
include_directories(${NLO_JSON_DIR})


add_executable(nlohman-json nlohman-json.cpp)
