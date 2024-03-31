
cmake_minimum_required(VERSION 3.10)

project(YF_SOFTWARE)

# 检查C++20标准是否可用
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)

if(COMPILER_SUPPORTS_CXX20)
    # 设置C++20标准
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True) # 强制要求此标准可用
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support.")
endif()

#add_subdirectory(src/thirdparty/nlohman-json)