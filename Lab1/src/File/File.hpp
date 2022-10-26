#pragma once
#include <fstream>
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
            std::string readLine();
            std::string read();
            bool readLine(std::string &str);
            bool isEnd();

            std::ostream& getStream();

        private:
            std::string file_name = "log.log";
            std::fstream* out = nullptr;
            std::ios::openmode mode = std::ios::in;

            void initStream();
    };
}
