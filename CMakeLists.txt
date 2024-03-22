
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(YF_SOFTWARE)

include_directories("E:/tools/x86_64-13.2.0-release-win32-seh-msvcrt-rt_v11-rev1/mingw64/x86_64-w64-mingw32/include")

add_subdirectory(src/thirdparty/nlohman-json)