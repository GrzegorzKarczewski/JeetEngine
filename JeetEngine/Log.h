#pragma once
#include <string>
#include <mutex>
#include <cstdarg>
#include <fstream>

class JeetLogger {
public:
    enum class LogLevel {
        INFO,
        WARNING,
        ERROR
    };

    // Singleton instance
    static JeetLogger& Get();

    // Initialize logger with output file
    bool Initialize(const std::string& logFilePath);

    // Log message with specified level
    void Log(LogLevel level, const std::string& message);

    // Convenience methods
    void Info(const char* fmt, ...);
    void Warning(const char* fmt, ...);
    void Error(const char* fmt, ...);

    // Cleanup
    void Shutdown();

private:
    JeetLogger();
    ~JeetLogger();

    std::string FormatMessage(LogLevel level, const std::string& message, bool colorize);

    std::ofstream logFile_;
    std::mutex mutex_;
};
