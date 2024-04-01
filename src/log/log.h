
#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

//#include "../../thirdparty/spdlog/include/spdlog/spdlog.h"
//#include "../../thirdparty/spdlog/include/spdlog/sinks/rotating_file_sink.h"
#include <memory>

class Logger {
public:
    Logger(const char* sinkname, const char* logname, spdlog::level::level_enum level);
    ~Logger(){};
private:
    std::shared_ptr<spdlog::sinks::rotating_file_sink_mt> sink;
public:
    std::shared_ptr<spdlog::logger> logger;
};

// log level
#define LOG_LEVEL_TRACE		        spdlog::level::trace
#define LOG_LEVEL_DBG		        spdlog::level::debug
#define LOG_LEVEL_INFO		        spdlog::level::info
#define LOG_LEVEL_WARN		        spdlog::level::warn
#define LOG_LEVEL_ERR		        spdlog::level::err
#define LOG_LEVEL_CRITICAL	        spdlog::level::critical
#define LOG_LEVEL_OFF		        spdlog::level::off

// system_logger->set
#define LOGC_LEVEL_SET(level)		spdlog::set_level(level)
#define LOGC_PATTERN_SET(fmt)		spdlog::set_pattern(fmt)

// console print
#define LOGC_DBG(...)		        spdlog::debug(__VA_ARGS__)
#define LOGC_INFO(...)		        spdlog::info(__VA_ARGS__)
#define LOGC_WARN(...)		        spdlog::warn(__VA_ARGS__)
#define LOGC_ERR(...)		        spdlog::error(__VA_ARGS__)
#define LOGC_CRITICAL(...)	        spdlog::critical(__VA_ARGS__)

std::shared_ptr<spdlog::logger> system_logger();

// file print set
#define LOGF_LEVEL_SET(level)		system_logger()->set_level(level)
#define LOGF_PATTERN_SET(fmt)		system_logger()->set_pattern(fmt)
#define LOGF_FLUSH_LEVEL_SET(level) system_logger()->flush_on(level)

// file print
#define LOGF_DBG(...)               system_logger()->debug(__VA_ARGS__)
#define LOGF_INFO(...)              system_logger()->info(__VA_ARGS__)
#define LOGF_WARN(...)              system_logger()->warn(__VA_ARGS__)
#define LOGF_ERR(...)		        system_logger()->error(__VA_ARGS__)
#define LOGF_CRITICAL(...)          system_logger()->critical(__VA_ARGS__)

// file print and console print
#define LOG_DBG(...)                do{ spdlog::debug(__VA_ARGS__); system_logger()->debug(__VA_ARGS__); } while (0)
#define LOG_INFO(...)               do{ spdlog::info(__VA_ARGS__); system_logger()->info(__VA_ARGS__); } while (0)
#define LOG_WARN(...)               do{ spdlog::warn(__VA_ARGS__); system_logger()->warn(__VA_ARGS__); } while (0)
#define LOG_ERR(...)                do{ spdlog::error(__VA_ARGS__); system_logger()->error(__VA_ARGS__); } while (0)
#define LOG_CRITICAL(...)           do{ spdlog::critical(__VA_ARGS__); system_logger()->critical(__VA_ARGS__); } while (0)