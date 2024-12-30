/*================================================================
*  Copyright (C)2024 All rights reserved.
*  FileName : main.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 30 Dec 2024 04:15:29 PM CST
================================================================*/

#include "cpptools.hh"

int main(int argc, char* argv[]) {
    std::string uuid = cpptools::generate_uuid4_12();
    std::cout << uuid << std::endl;

    return 0;
}
