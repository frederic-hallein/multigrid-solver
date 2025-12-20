#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

// TODO : make {} usable for other types besides vector
namespace logger {
    inline std::string current_time() {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");
        return oss.str();
    }

    template <typename T>
    std::string format_vec(const std::vector<T>& vec) {
        std::ostringstream oss;
        oss << "(";
        for (size_t i = 0; i < vec.size(); ++i) {
            oss << vec[i];
            if (i + 1 < vec.size()) oss << ", ";
        }
        oss << ")";
        return oss.str();
    }

    inline void info(const std::string& msg) {
        std::cout << "[" << current_time() << "] [INFO] " << msg << '\n';
    }

    template <typename T>
    inline void info(const std::string& msg, const std::vector<T>& vec) {
        size_t pos = msg.find("{}");
        if (pos != std::string::npos && !vec.empty()) {
            std::string formatted = msg;
            formatted.replace(pos, 2, format_vec(vec));
            std::cout << "[" << current_time() << "] [INFO] " << formatted << '\n';
        } else {
            std::cout << "[" << current_time() << "] [INFO] " << msg << '\n';
        }
    }

    inline void warning(const std::string& msg) {
        std::cout << "[" << current_time() << "] [WARNING] " << msg << '\n';
    }

    template <typename T>
    inline void warning(const std::string& msg, const std::vector<T>& vec) {
        size_t pos = msg.find("{}");
        if (pos != std::string::npos && !vec.empty()) {
            std::string formatted = msg;
            formatted.replace(pos, 2, format_vec(vec));
            std::cout << "[" << current_time() << "] [WARNING] " << formatted << '\n';
        } else {
            std::cout << "[" << current_time() << "] [WARNING] " << msg << '\n';
        }
    }

    inline void error(const std::string& msg) {
        std::cout << "[" << current_time() << "] [ERROR] " << msg << '\n';
    }

    template <typename T>
    inline void error(const std::string& msg, const std::vector<T>& vec) {
        size_t pos = msg.find("{}");
        if (pos != std::string::npos && !vec.empty()) {
            std::string formatted = msg;
            formatted.replace(pos, 2, format_vec(vec));
            std::cout << "[" << current_time() << "] [ERROR] " << formatted << '\n';
        } else {
            std::cout << "[" << current_time() << "] [ERROR] " << msg << '\n';
        }
    }
}