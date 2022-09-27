#include "Exception.hpp"
#include <bits/types/error_t.h>
#include <fstream>
#include <chrono>
#include <iterator>

namespace YMM {
    Exception::Exception(std::string error) {
        this->error_msg = error;
        logging(this->error_msg);
    }

    Exception::Exception() {}

    Exception::~Exception() {}

    void Exception::logging(std::string msg, std::string log_type) {
        std::fstream file;
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        file.open(file_name, std::ios::app);
        if (file.is_open()) {
            file << "[LOG] << " << log_type << ": " << std::ctime(&end_time) << " " << msg.c_str() << "\n";
            file.close();
        }
    }

    void Exception::logging(std::string msg) {
        logging(msg, log_type_error);
    }

    void Exception::error(std::string msg) {
        // this->error_msg = msg;
        logging(msg, log_type_error);
    }

    void Exception::warning(std::string msg) {
        // this->warning_msg = msg;
        logging(msg, log_type_warning);
    }
}
