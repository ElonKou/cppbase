/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : test_timer.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Sat 20 Aug 2022 06:37:16 PM CST
================================================================*/

#include "cpptools.hpp"

using namespace cpptools;

int main(int argc, char* argv[]) {

    Timer t;
    t.Start();

    int sum = 0;
    for (size_t k = 0; k < 4; k++) {
        for (size_t i = 0; i < 64 * 1024 * 1024; i++) {
            sum = sum + i;
        }
        std::cout << t.StopMS() << " ms" << std::endl;
    }

    return 0;
}
