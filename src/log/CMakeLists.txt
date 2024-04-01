

message("include_directories: ${INCLUDE_SPDLOG_PATH}")

add_executable(log_test log_test.cpp log.cpp log.h)
target_link_libraries(log_test spdlog)