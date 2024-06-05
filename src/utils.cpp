#include "utils.hpp"

bool check_header(Header header) {
  if (header.get_code() == 0) {
    return true;
  } else {
    return false;
  }
}


