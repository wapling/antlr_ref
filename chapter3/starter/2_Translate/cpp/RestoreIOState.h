#pragma once

#include <ostream>

struct RestoreIOState
{
  std::ostream& ostream_;
  std::ios_base::fmtflags const flags_;

  RestoreIOState(std::ostream& ostream) :
    ostream_(ostream),
    flags_(ostream_.flags())    
  {}

  ~RestoreIOState()
  {
    ostream_.flags(flags_);
  }
};

