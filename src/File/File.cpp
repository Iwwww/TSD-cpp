#include "File.hpp"
#include <fstream>
#include <string>

namespace YMM {
    File::File() {}

    File::File(std::string file_name, std::string mode) {
        open(file_name, mode);
    }

    File::~File() {}

    void File::setFileName(std::string file_name) {
        this->file_name = file_name;
    }

    void File::initStream() {
        if (this->isOpen()) {
            this->out->close();
        }
        std::fstream* out = new std::fstream;
        this->out = out;
    }

    void File::open(std::string file_name, std::string _mode) {
        this->setFileName(file_name);
        this->initStream();

        if (_mode == "r") 
            this->mode = std::ios::in;
        else if (_mode == "w")
            this->mode = std::ios::out;
        else if (_mode == "rw")
            this->mode =  std::ios::in | std::ios::out;
        else if (_mode == "append")
            this->mode =  std::ios::app;
        else
            this->mode = std::ios::in;

        this->out->open(file_name, this->mode); 
    }

    void File::close() {
        if (isOpen()) {
            this->out->close();
        }
    }

    bool File::isOpen() {
        bool flag = 0;
        if (this->out != nullptr) {
            if (this->out->is_open()) {
                flag = 1;
            }
        }

        return flag;
    }

    void File::write(std::string text) {
        if (isOpen()) {
            *this->out << text;
        }
    }

    std::string File::readLine() {
        std::string line{};
        if (this->mode == std::ios::in || this->mode == std::ios::ate || std::ios::in | std::ios::out) {
            std::getline(*this->out, line);
        }
        return line;
    }

    std::string File::read() {
        std::string line{};
        std::string text{};
        if (this->mode == std::ios::in || this->mode == std::ios::ate || std::ios::in | std::ios::out) {
            while (std::getline(*this->out, line)) {
                text += line;
            }
        }
        return text;
    }
}
