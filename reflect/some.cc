/*================================================================
*  Copyright (C)2021 All rights reserved.
*  FileName : some.cc
*  Author   : dlkou
*  Email    : elonkou@ktime.cc
*  Date     : Mon 12 Sep 2022 01:42:00 PM CST
================================================================*/

#include "some.hh"

void some() {
    std::shared_ptr<Base> p2((Base*)Reflector::Instance()->CreateObject("DeriveA"));
    p2->Print();

    std::shared_ptr<Base> p3((Base*)Reflector::Instance()->CreateObject("DeriveB"));
    p3->Print();
}
