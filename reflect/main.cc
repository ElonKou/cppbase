/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : main.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 12 Sep 2022 03:08:37 PM CST
================================================================*/

#include "some.hh"

std::shared_ptr<Reflector> Reflector::ptr = nullptr;

int main(int argc, char* argv[]) {
    some();
    return 0;
}
