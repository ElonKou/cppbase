/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : test_cpptools.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "cpptools.hh"
#include <iostream>

using namespace cpptools;

int main(int argc, char* argv[]) {
    int         a = 23;
    float       b = 23.23;
    double      c = 213.33;
    std::string d = "some info";

    PrintInfo(std::to_string(a) + "\n", INFO_TYPE::WARNING);
    PrintInfo(std::to_string(b) + "\n", INFO_TYPE::SUCCEED);
    PrintInfo(std::to_string(c) + "\n", INFO_TYPE::ERROR);
    PrintInfo(d + "\n", INFO_TYPE::OK);
    PrintInfo(d + "\n", INFO_TYPE::SUCCEED);
    return 0;
}
