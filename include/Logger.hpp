#pragma once

#include <iostream>
#include <string>

enum class LogLevel { Debug = 0, Info = 1, Warn = 2, Error = 3 };

class Logger {
public:
    static void setLevel(LogLevel level);

    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warn(const std::string& message);
    static void error(const std::string& message);

private:
    static LogLevel currentLevel;
    static void log(LogLevel level, const std::string& message);
};
