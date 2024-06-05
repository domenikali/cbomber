#ifndef DOMES_LIBRARY_H
#define DOMES_LIBRARY_H

#include <iostream>

#define DEBUG true

enum log_level {
    INFO,
    WARNING,
    ERROR
};

#define ERROR_COLOR "\033[31m" //red
#define WARNING_COLOR "\033[33m" //yellow
#define INFO_COLOR "\033[36m" //cyan
#define RESET "\033[0m"

/**
 *  @brief print a message with a color
 *  @param level the log level
 *  @param message the message to print
 */
void print(const log_level level, const std::string message);


#endif