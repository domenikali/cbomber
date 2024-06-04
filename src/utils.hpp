#ifndef UTILS_H
#define UTILS_H

#include <iostream>
using namespace std;

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

void print(log_level level, string message);

#endif