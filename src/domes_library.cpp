#include "domes_library.hpp"

void print(log_level level, std::string message) {
  if (DEBUG) {
    switch (level) {
      case INFO:
        std::cout << INFO_COLOR << "INFO: " << message;
        break;
      case WARNING:
        std::cout << WARNING_COLOR << "WARNING: " << message;
        break;
      case ERROR:
        std::cout << ERROR_COLOR << "ERROR: " << message;
        break;
    }
    std::cout << RESET << std::endl;
  }
}