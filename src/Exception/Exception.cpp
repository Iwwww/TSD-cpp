#include "Exception.hpp"
#include "../File/File.hpp"
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
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::string line = std::string("[LOG] << " + log_type + ": " + std::ctime(&end_time) + " " + msg.c_str() + "\n");

        File file("../log.log", "w");
        file.write(line);

    }

    void Exception::logging(std::string msg) {
        logging(msg, log_type_error);
    }

    void Exception::error(std::string msg) {
        logging(msg, log_type_error);
    }

    void Exception::warning(std::string msg) {
        logging(msg, log_type_warning);
    }
}
