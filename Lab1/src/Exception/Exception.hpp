#pragma once
#include "../File/File.hpp"
#include <chrono>
#include <string>

namespace YMM {
class Exception {
public:
  static void logging(std::string, std::string);
  static void error(std::string);
  static void warning(std::string);
  static void info(std::string);

  static void setLogFileName(std::string file_name);
  static std::string getLogFileName();

private:
  static std::string log_file_name;
};
} // namespace YMM
