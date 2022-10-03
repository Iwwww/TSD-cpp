#pragma once
#include <fstream>
#include <ios>
#include <string>

namespace YMM {
    class File {
        public:
            File();
            File(std::string file_name, std::string mode);
            ~File();

            void setFileName(std::string);
            void open(std::string file_name, std::string mode);
            void close();
            bool isOpen();
            void write(std::string);
            std::string read();

            std::ostream& getStream();

        private:
            std::string file_name{};
            std::fstream* out = nullptr;
            std::ios::openmode mode{};

            void initStream();
    };
}
