/*================================================================
*  Copyright (C)2022 All rights reserved.
*  FileName : test_cpptools.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Sun May 15 11:32:39 2022
================================================================*/

#include "cpptools.hpp"
#include <iostream>

using namespace cpptools;

int main(int argc, char* argv[]) {
    PrintInfo(std::to_string(31231313), INFO_TYPE::WARNING);
    PrintInfo("dsadaweqwe31d\n\nsss", INFO_TYPE::WARNING);
    return 0;
}
