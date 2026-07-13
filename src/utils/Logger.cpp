#include "Logger.h"
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

Logger::~Logger() {
    close();
}

void Logger::init(const std::string& filename, Level minLevel) {
    if (isInitialized) {
        logFile.close();
    }

    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "[Logger] Cannot open log file: " << filename << std::endl;
        return;
    }

    minLogLevel = minLevel;
    isInitialized = true;
    info("=== Logger initialized ===");
}

// Đóng file log
void Logger::close() {
    if (logFile.is_open()) {
        info("=== Logger closed ===");
        logFile.close();
    }
    isInitialized = false;
}

void Logger::debug(const std::string& message) {
    log(DEBUG, message);
}

void Logger::info(const std::string& message) {
    log(INFO, message);
}

void Logger::warning(const std::string& message) {
    log(WARNING, message);
}

void Logger::error(const std::string& message) {
    log(ERROR, message);
}

void Logger::log(Level level, const std::string& message) {
    if (level < minLogLevel) return;
    writeLog(level, message);
}

std::string Logger::levelToString(Level level) const {
    switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARN";
        case ERROR:   return "ERROR";
        default:      return "UNKNOWN";
    }
}

std::string Logger::getCurrentTime() const {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                  now.time_since_epoch()
              ) % 1000;

    std::tm tm;
#ifdef _WIN32
    localtime_s(&tm, &time_t_now);
#else
    localtime_r(&time_t_now, &tm);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S")
        << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return oss.str();
}

void Logger::writeLog(Level level, const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);

    std::string timeStr = getCurrentTime();
    std::string levelStr = levelToString(level);
    std::string logLine = "[" + timeStr + "] [" + levelStr + "] " + message;

    if (level >= INFO) {
        if (level == ERROR) {
            std::cerr << logLine << std::endl;
        } else {
            std::cout << logLine << std::endl;
        }
    }

    if (logFile.is_open()) {
        logFile << logLine << std::endl;
        logFile.flush();
    }
}
