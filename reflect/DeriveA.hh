#pragma once

#include "Base.hh"

class DeriveA : public Base {
  public:
    void Print() override;
};
REGISTER(DeriveA);