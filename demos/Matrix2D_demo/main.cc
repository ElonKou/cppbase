/*================================================================
*  Copyright (C)2025 All rights reserved.
*  FileName : main.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Thu 09 Jan 2025 02:17:50 PM CST
================================================================*/

#include "cpptools.hh"

#include <iostream>
#include <vector>

class Item {
  public:
    int v;
    Item() { std::cout << "Item Created" << std::endl; }
    ~Item() { std::cout << "Item [DDD]" << std::endl; }
};

int main(int argc, char* argv[]) {
    cppt::Matrix<int> m = cppt::Matrix<int>(2, 3);
    m(0, 0)             = 8;
    m(0, 1)             = 41;
    m(0, 2)             = 280;
    m(1, 0)             = 2;
    m(1, 1)             = 48;
    m(1, 2)             = 32;
    std::cout << m << std::endl;

    std::vector<float> cdata = {1, 2, 2, 34, 5, 5, 6, 7, 7, 8, 8, 9};

    auto m1 = cppt::Matrix<float>(3, 4, cdata.data());
    auto m2 = cppt::Matrix<float>(3, 4, cdata);
    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    cppt::Matrix<Item> m3 = cppt::Matrix<Item>(2, 2);
    cppt::Matrix<Item> m4 = cppt::Matrix<Item>(3, 4);
    m3                    = m4;

    return 0;
}
