#include "Exception.hpp"

namespace YMM {
    void Exception::logging(std::string msg, std::string log_type) {
        auto now = std::chrono::system_clock::now();
        time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::string line = std::string("[LOG] << " + log_type + ": " + std::ctime(&end_time) + " " + msg.c_str() + "\n");

        File file(log_file_name, "append");
        file.write(line);
        file.close();
    }

    void Exception::error(std::string msg) {
        logging(msg, std::string("ERROR"));
    }

    void Exception::warning(std::string msg) {
        logging(msg, std::string("WARN"));
    }

    void Exception::info(std::string msg) {
        logging(msg, std::string("INFO"));
    }

    void Exception::setLogFileName(std::string file_name) {
        log_file_name = file_name;
    }

    std::string Exception::getLogFileName() {
        return log_file_name;
    }
}
