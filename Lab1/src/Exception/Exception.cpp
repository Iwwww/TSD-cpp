#include "Exception.hpp"
#include <string>

namespace YMM {
    Exception::Exception(std::string error) {
        this->error_msg = error;
        logging(this->error_msg);
    }

    Exception::Exception(std::string error, std::string file_name) {
        setFileName(file_name);
        this->error_msg = error;
        logging(this->error_msg);
    }

    Exception::Exception() {}

    Exception::~Exception() {}

    void Exception::logging(std::string msg, std::string log_type) {
        auto now = std::chrono::system_clock::now();
        time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::string line = std::string("[LOG] << " + log_type + ": " + std::ctime(&end_time) + " " + msg.c_str() + "\n");

        File file(this->file_name, "append");
        file.write(line);
        file.close();

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

    void Exception::setFileName(std::string file_name) {
        this->file_name = file_name;
    }
}
