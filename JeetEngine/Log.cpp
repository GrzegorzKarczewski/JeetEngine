#include "Log.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <fstream>

JeetLogger& JeetLogger::Get() {
    static JeetLogger instance;
    return instance;
}

bool JeetLogger::Initialize(const std::string& logFilePath) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile_.is_open()) {
        logFile_.close();
    }
    logFile_.open(logFilePath, std::ios::out | std::ios::app);
    return logFile_.is_open();
}

void JeetLogger::Log(LogLevel level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    // Color for console, plain for file
    std::string formattedMessageColor = FormatMessage(level, message, true);
    std::string formattedMessagePlain = FormatMessage(level, message, false);
    // Output to console
    std::cout << formattedMessageColor << std::endl;

    // Output to file if open
    if (logFile_.is_open()) {
        logFile_ << formattedMessagePlain.c_str() << std::endl;
        logFile_.flush();
    }
}

void JeetLogger::Info(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    Log(LogLevel::INFO, buffer);
}
void JeetLogger::Warning(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    Log(LogLevel::WARNING, buffer);
}
void JeetLogger::Error(const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    Log(LogLevel::ERROR, buffer);
}

void JeetLogger::Shutdown() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (logFile_.is_open()) {
        logFile_.close();
    }
}

JeetLogger::JeetLogger() = default;

JeetLogger::~JeetLogger() { Shutdown(); }

std::string JeetLogger::FormatMessage(LogLevel level, const std::string& message, bool colorize) {
    std::string levelStr, color;
    switch (level) {
    case LogLevel::INFO:    levelStr = "INFO";    color = "\033[32m"; break;
    case LogLevel::WARNING: levelStr = "WARNING"; color = "\033[33m"; break;
    case LogLevel::ERROR:   levelStr = "ERROR";   color = "\033[31m"; break;
    }

    // Get current time
    char buf[64];
    std::time_t now = std::time(nullptr);
    ctime_s(buf, sizeof(buf), &now);
    std::string timestamp = buf;
    timestamp.pop_back(); // remove newline

    std::string output = "[" + timestamp + "] [" + levelStr + "] " + message;
    return colorize ? (color + output + "\033[0m") : output;
}