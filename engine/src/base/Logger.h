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
    std::string formattedLog =
        fmt::format(fmt::runtime("[{:%F %T UTC%z}] Jupiter Log: "), fmt::localtime(t));
    formattedLog += fmt::vformat(msg, fmt::make_format_args(args...));
    switch (level) {
    case TRACE:
        formattedLog =
            fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(WHITE)), fmt::runtime(formattedLog));
        break;
    case INFO:
        formattedLog =
            fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(GREEN)), fmt::runtime(formattedLog));
        break;
    case WARN:
        formattedLog =
            fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(YELLOW)), fmt::runtime(formattedLog));
        break;
    case ERROR:
        formattedLog =
            fmt::format(fmt::emphasis::bold | fmt::fg(fmt::rgb(RED)), fmt::runtime(formattedLog));
        break;
    case CRITICAL:
        formattedLog =
            fmt::format(fmt::emphasis::bold | fmt::bg(fmt::rgb(RED)), fmt::runtime(formattedLog));
        break;
    }

    fmt::print("{}\n", formattedLog);
}

}  // namespace jupiter

// Auxiliary macros
#define VA_ARGS(...) , ##__VA_ARGS__

// Logging macros
#define JLOG_TRACE(msg, ...) jupiter::Logger::logTrace(jupiter::LogLevel::TRACE, msg, ##__VA_ARGS__)
#define JLOG_INFO(msg, ...) jupiter::Logger::logTrace(jupiter::LogLevel::INFO, msg, ##__VA_ARGS__)
#define JLOG_WARN(msg, ...) jupiter::Logger::logTrace(jupiter::LogLevel::WARN, msg, ##__VA_ARGS__)
#define JLOG_ERROR(msg, ...) jupiter::Logger::logTrace(jupiter::LogLevel::ERROR, msg, ##__VA_ARGS__)
#define JLOG_CRITICAL(msg, ...) \
    jupiter::Logger::logTrace(jupiter::LogLevel::CRITICAL, msg, ##__VA_ARGS__)
