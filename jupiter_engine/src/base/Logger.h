#pragma once

// Own includes
#include "base/Defines.h"

// Third party includes
#define FMT_HEADER_ONLY
#include <fmt/color.h>
#include <fmt/chrono.h>

namespace jupiter {

enum LogLevel : uint8 { TRACE, INFO, WARN, ERROR, CRITICAL };

enum LogColor : uint32 { WHITE = 0xFFFFFF, GREEN = 0x008000, YELLOW = 0xFFFF00, RED = 0xFF0000 };

class Logger {
public:
    template <typename... Args>
    static void logTrace(LogLevel level, const char* msg, Args&&... args);
};

template <typename... Args>
void Logger::logTrace(LogLevel level, const char* msg, Args&&... args) {
    std::time_t t = std::time(nullptr);
    std::string formatedLog = fmt::format("[{:%F %T UTC%z}] Jupiter Log: ", fmt::localtime(t));
    formatedLog += fmt::vformat(msg, fmt::make_format_args(args...));
    switch (level) {
    case TRACE:
        formatedLog = fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(WHITE)), formatedLog);
        break;
    case INFO:
        formatedLog = fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(GREEN)), formatedLog);
        break;
    case WARN:
        formatedLog = fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(YELLOW)), formatedLog);
        break;
    case ERROR:
        formatedLog = fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(RED)), formatedLog);
        break;
    case CRITICAL:
        formatedLog = fmt::format(fmt::emphasis::bold | fmt::bg(fmt::rgb(RED)), formatedLog);
        break;
    }

    fmt::print("{}\n", formatedLog);
}

}  // namespace jupiter

// Auxiliary macros
#define VA_ARGS(...) , ##__VA_ARGS__

// Logging macros
#define JLOG_TRACE(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::TRACE, msg VA_ARGS(__VA_ARGS__))
#define JLOG_INFO(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::INFO, msg VA_ARGS(__VA_ARGS__))
#define JLOG_WARN(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::WARN, msg VA_ARGS(__VA_ARGS__))
#define JLOG_ERROR(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::ERROR, msg VA_ARGS(__VA_ARGS__))
#define JLOG_CRITICAL(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::CRITICAL, msg VA_ARGS(__VA_ARGS__))
