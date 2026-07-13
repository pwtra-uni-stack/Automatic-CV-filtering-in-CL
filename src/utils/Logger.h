#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <mutex>

class Logger {
public:
    // Các mức độ log
    enum Level {
        DEBUG,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& getInstance();

    void init(const std::string& filename = "logs.txt", Level minLevel = INFO);

    void debug(const std::string& message);
    void info(const std::string& message);
    void warning(const std::string& message);
    void error(const std::string& message);

    // Ghi log với mức độ tùy chỉnh
    void log(Level level, const std::string& message);

    void close();

private:
    // Constructor private (Singleton)
    Logger() = default;
    ~Logger();

    // Không cho phép copy
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::string levelToString(Level level) const;

    std::string getCurrentTime() const;

    void writeLog(Level level, const std::string& message);

private:
    std::ofstream logFile;
    Level minLogLevel = INFO;
    std::mutex mtx;
    bool isInitialized = false;
};

// ==================== MACRO TIỆN ÍCH ====================

#define LOG_DEBUG(msg) Logger::getInstance().debug(msg)
#define LOG_INFO(msg)  Logger::getInstance().info(msg)
#define LOG_WARN(msg)  Logger::getInstance().warning(msg)
#define LOG_ERROR(msg) Logger::getInstance().error(msg)

#endif // LOGGER_H