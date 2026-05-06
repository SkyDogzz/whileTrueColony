#include "Logger.hpp"

LogLevel Logger::currentLevel = LogLevel::Info;

void Logger::setLevel(LogLevel level) { currentLevel = level; }

void Logger::log(LogLevel level, const std::string& message)
{
    if (level == LogLevel::Debug) {
        std::cout << "[DEBUG]";
    } else if (level == LogLevel::Info) {
        std::cout << "[INFO]";
    } else if (level == LogLevel::Warn) {
        std::cout << "[WARN]";
    } else if (level == LogLevel::Error) {
        std::cout << "[ERROR]";
    } else
        std::cout << "[UNKNOWN]";

    std::cout << ": " << message << std::endl;
}

void Logger::debug(const std::string& message)
{
    if (currentLevel <= LogLevel::Debug)
        log(LogLevel::Debug, message);
}

void Logger::info(const std::string& message)
{
    if (currentLevel <= LogLevel::Info)
        log(LogLevel::Info, message);
}

void Logger::warn(const std::string& message)
{
    if (currentLevel <= LogLevel::Warn)
        log(LogLevel::Warn, message);
}

void Logger::error(const std::string& message)
{
    if (currentLevel <= LogLevel::Error)
        log(LogLevel::Error, message);
}
