
cmake_minimum_required(VERSION 3.10)

project(YF_SOFTWARE)


set(INCLUDE_SPDLOG_PATH "${CMAKE_SOURCE_DIR}/thirdparty/spdlog/include")
set(LIB_SPDLOG_PATH "${CMAKE_SOURCE_DIR}/thirdparty/spdlog/lib")

include_directories(${INCLUDE_SPDLOG_PATH})
message("spd include path : ${INCLUDE_SPDLOG_PATH} ")
link_directories(${LIB_SPDLOG_PATH})

# 检查C++20标准是否可用
#[[
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
]]


add_subdirectory(src)

add_executable(YF_SOFTWARE main.cpp)
#[[if(COMPILER_SUPPORTS_CXX20)
    # 设置C++20标准
    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True) # 强制要求此标准可用
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++20 support.")
endif()]]

#add_subdirectory(src/thirdparty/nlohman-json)