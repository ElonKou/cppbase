#pragma once

#include "RefBase.hh"

class DeriveA : public Base {
  public:
    void Print() override;
};
REGISTER_APPLICATION(DeriveA);