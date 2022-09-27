#pragma once
#include <fstream>
#include <string>

namespace YMM {
    class Exception {
        public:
            Exception(std::string);
            Exception();
            ~Exception();
            
            void logging(std::string);
            void error(std::string);
            void warning(std::string);
            void setFileName(std::string);
        
        private:
            std::string error_msg{};
            std::string warning_msg{};
            std::string file_name = "log.log";
            std::string log_type_error = "ERROR";
            std::string log_type_warning = "WARN";

            void logging(std::string, std::string);
    };
}
