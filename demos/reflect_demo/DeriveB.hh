#pragma once

#include "RefBase.hh"

class DeriveB : public Base {
  public:
    void Print() override;
};
REGISTER_APPLICATION(DeriveB);
