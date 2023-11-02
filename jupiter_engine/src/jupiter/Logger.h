#pragma once

// C++ system includes
#include <memory>

// Own includes
#include "Core.h"

// Third-party includes
#include "spdlog/spdlog.h"

namespace jupiter {

class JUPITER_API Logger {
public:
    static void init();

    static std::shared_ptr<spdlog::logger>& getLogger();

private:
    static std::shared_ptr<spdlog::logger> logger;
};

}  // namespace jupiter

#define LOG_TRACE(...) jupiter::Logger::getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...) jupiter::Logger::getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) jupiter::Logger::getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) jupiter::Logger::getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) jupiter::Logger::getLogger()->critical(__VA_ARGS__)
