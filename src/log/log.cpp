
#include "log.h"
#include <memory>
#include <string>
#include <cstdio>
#include <ctime>

Logger::Logger(const char* sinkname, const char* logname, spdlog::level::level_enum level)
{
    time_t now;
    time(&now);
    struct tm* t = localtime(&now);
    char buf[30] = { 0 };
    snprintf(buf, 30, "%d%02d%02d-%02d%02d%02d", t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    std::string logfile = ".log/" + std::string(sinkname) + "[" + buf + "]" + ".txt";
    sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logfile, 1024 * 1024 * 10, 5);
    logger = std::make_shared<spdlog::logger>(logname, sink);
    logger->set_level(level);
    logger->set_pattern("[%Y%m%d-%H%M%S.%e](%n)<%L> %v");
    logger->flush_on(LOG_LEVEL_INFO);
}

static Logger syslog("log-system", "SYSTEM", LOG_LEVEL_INFO);

std::shared_ptr<spdlog::logger> system_logger()
{
    return syslog.logger;
}