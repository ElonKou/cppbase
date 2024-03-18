#pragma once

#ifndef BASE
#define BASE

#include "Reflector.hh"

class Base {
  public:
    explicit Base() = default;
    virtual void Print() {
        std::cout << "Base" << std::endl;
    }
};
// REGISTER(Base);

#endif