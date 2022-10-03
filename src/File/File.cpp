#include "File.hpp"
#include <fstream>

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
        } else {
            std::fstream out;
            this->out = &out;
        }
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
        } else {
            this->exception.warning("Empty Stream Ptr");
        }

        return flag;
    }

    void File::write(std::string text) {
        *out << text;
    }

    std::string File::read() {
        std::string text{};
        char line[100];
        if (this->mode == std::ios::in || this->mode == std::ios::ate) {
            while (this->out->getline(line, 100)) {
                text += line;
            }
        } else {
            // this->exception.error(&"Invalid reading mode: " [this->mode]);
        }
    }
}
