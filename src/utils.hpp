#ifndef UTILS_H
#define UTILS_H

#include "packets.hpp"
#include <iostream>

using std::string, std::cout, std::endl;

const Header Header_Ok = Header(0,0,0);
const Header Header_Err = Header(1,0,0);



#endif