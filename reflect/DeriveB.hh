#pragma once

#include "Base.hh"

class DeriveB : public Base {
  public:
    void Print() override;
};
REGISTER(DeriveB);
