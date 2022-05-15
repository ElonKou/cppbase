/*================================================================
*  Copyright (C)2020 All rights reserved.
*  FileName : test.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon Nov 15 13:17:30 2021
================================================================*/

#include "cpptypes.hpp"
#include <iostream>

using namespace std;
using namespace cpptypes;

void test_creator() {
    // creator
    vec2i a;
    vec2i b(2, 3);
    vec2i c(2.3, 2.9);
    vec2i d(b);
    vec2f e(3.33, 4.55);
    vec2i f(e);
    vec2f y(2.3, 55.1);
    vec2i x = y;
    vec2i z = vec2f(2.3, 55.1);
    std::cout << a << std::endl; // 0,0
    std::cout << b << std::endl; // 2,3
    std::cout << b << std::endl; // 2,3
    std::cout << d << std::endl; // 2,3
    std::cout << e << std::endl; // 3.33,4.55
    std::cout << f << std::endl; // 3,4
    std::cout << x << std::endl; // 2,55
    std::cout << z << std::endl; // 2,55
}

void test_add() {
    // vec2i add same type
    vec2i a(3, 4);
    vec2i b(2, 3);
    vec2f c(2.23, 3.34);
    vec2f d(10.02, 8.01);
    vec2f e = a + b;
    vec2f f = c + d;

    std::cout << a + b << std::endl;        // 5,7
    std::cout << e << std::endl;            // 5,7
    std::cout << c + d << std::endl;        // 12.25,11.35
    std::cout << f << std::endl;            // 12.25,11.35
    std::cout << a + d << std::endl;        // 13,12
    std::cout << vec2f(a) + d << std::endl; // 13.02,12.01
    std::cout << d + a << std::endl;        // 13.02,12.01
}

void test_multipy() {
    // assigmnet different types.
    vec2f x(2.1, 2.2);
    vec2f y(2.1, 2.2);
    vec2f u = x * 2.1;
    vec2f v = x * 3;
    std::cout << x << std::endl;     // 2.1,2.2
    std::cout << x * y << std::endl; // 9.25
    std::cout << u << std::endl;     // 4.41,4.62
    std::cout << v << std::endl;     // 6.3,6.6
}

void mat_creator() {
    Mat2i m1(Dim2(3, 4));
    std::cout << m1 << std::endl;
    m1.seteyes();
    std::cout << m1 << std::endl;
    m1.setones();
    std::cout << m1 << std::endl;
    m1.setlines();
    std::cout << m1 << std::endl;
    m1.reshape(Dim2(4, 3));
    std::cout << m1 << std::endl;
    m1.T();
    std::cout << m1 << std::endl;
}

void mat_vec() {
    Mat3i m(Dim3(3, 4, 2));
    m.setlines();
    std::cout << m << std::endl;

    Mat2i x = m.getpals(1);
    std::cout << x << std::endl;
}

int main(int argc, char* argv[]) {
    // test_creator();
    // test_add();
    // test_multipy();

    // mat_creator();
    mat_vec();
    return 0;
}
