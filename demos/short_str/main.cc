/*================================================================
*  Copyright (C)2025 All rights reserved.
*  FileName : main.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Tue 07 Jan 2025 05:53:25 PM CST
================================================================*/

#include <gtest/gtest.h>

#include "cpptools.hh"

using namespace cpptools;

TEST(Constructor, CreateTest) {
    str8 str8_1;                                  // default constructor
    str8 str8_2 = "ioiooioiooooo-";               // copy constructor: char *
    str8 str8_3 = std::string(":sdasdasd:sdasd"); // copy constructor: std::string
    str8 str8_4 = std::string(":");               // copy constructor: 1 size
    str8 str8_5 = str8_2;                         // copy constructor: different type

    EXPECT_STREQ("", str8_1.c_str());
    EXPECT_STREQ("ioiooio", str8_2.c_str());
    EXPECT_STREQ(":sdasda", str8_3.c_str());
    EXPECT_STREQ(":", str8_4.c_str());
    EXPECT_STREQ("ioiooio", str8_5.c_str());
};

TEST(Constructor, MemblerTest) {
    str8 str8_1;
    str8 str8_2 = "ioiooioiooooo-";
    str8 str8_3 = std::string(":sdasdasd:sdasd");

    EXPECT_EQ(0, str8_1.size());
    EXPECT_EQ(7, str8_2.size());
    EXPECT_EQ(7, str8_3.size());

    EXPECT_EQ(8, str8_1.capacity());
    EXPECT_EQ(8, str8_2.capacity());
    EXPECT_EQ(8, str8_3.capacity());

    str8_2[2]    = '_';
    str8_2.at(5) = '=';
    EXPECT_STREQ("io_oo=o", str8_2.c_str());
};

TEST(Constructor, AssignTest) {
    str16 str16_1 = "sdasdasdasd-a-s-s--s-s---";
    str16 str16_2 = str16_1;
    str16 str16_3 = "s";

    EXPECT_STREQ("sdasdasdasd-a-s", str16_1.c_str());
    EXPECT_STREQ("sdasdasdasd-a-s", str16_2.c_str());
    EXPECT_STREQ("s", str16_3.c_str());

    str8 str8_4;
    str8 str8_5 = 'v';
    str8_4      = str16_1;
    str16_3     = str8_5;
    EXPECT_STREQ("sdasdas", str8_4.c_str());
    EXPECT_STREQ("v", str8_5.c_str());
    EXPECT_STREQ("v", str16_3.c_str());

    str8  str8_6;
    str16 str16_7 = "sss";

    std::string xx = std::string("dsasda00sdadas000000000000");
    str8_6         = "dsasda00sdadas000000000000";
    str16_7        = xx;
    EXPECT_STREQ("dsasda0", str8_6.c_str());
    EXPECT_STREQ("dsasda00sdadas0", str16_7.c_str());
};

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
