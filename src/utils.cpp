#include "utils.hpp"

void print(log_level level, string message) {
    if (DEBUG) {
        switch (level) {
            case INFO:
                cout << INFO_COLOR << "INFO: " << message;
                break;
            case WARNING:
                cout << WARNING_COLOR << "WARNING: " << message;
                break;
            case ERROR:
                cout << ERROR_COLOR << "ERROR: " << message;
                break;
        }
        cout << RESET << endl;
    }
}
