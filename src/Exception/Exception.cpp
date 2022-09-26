#include "Exception.hpp"
#include <fstream>
#include <chrono>
#include <iterator>

namespace YMM {
    Exception::Exception(std::string error) {
        this->error = error;
        logging();
    }

    Exception::~Exception() {}

    void Exception::logging() {
        std::fstream file;
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        file.open("log.log", std::ios::app);
        if (file.is_open()) {
            file << "[LOG] ERROR: " << std::ctime(&end_time) << " " << this->error.c_str() << "\n";
            file.close();
        }
    }
}
