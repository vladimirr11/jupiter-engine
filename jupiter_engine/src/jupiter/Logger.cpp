// Corresponding header
#include "Logger.h"

// Third-party includes
#include "spdlog/sinks/stdout_color_sinks.h"

namespace jupiter {

std::shared_ptr<spdlog::logger> Logger::logger;

void Logger::init() {
    spdlog::set_pattern("[%H:%M:%S] %n: %v%$");
    logger = spdlog::stdout_color_mt("Jupiter");
    logger->set_level(spdlog::level::trace);
}

std::shared_ptr<spdlog::logger>& Logger::getLogger() { return logger; }

}  // namespace jupiter