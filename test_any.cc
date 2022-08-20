/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : test_any.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat 20 Aug 2022 06:50:38 PM CST
================================================================*/

#include "cpptools.hpp"
#include <iostream>

using namespace cpptools;

int main(int argc, char* argv[]) {
    int         x = 10;
    float       y = 78.98;
    std::string z = "sdasdasda";

    Any a = z;
    Any b = y;
    Any c(x);
    Any d(b);
    Any e = c;

    std::cout << a.get<std::string>() << std::endl;
    std::cout << b.get<float>() << std::endl;
    std::cout << c.get<int>() << std::endl;
    std::cout << d.get<float>() << std::endl;
    std::cout << e.get<int>() << std::endl;

    return 0;
}
