#pragma once

#include "Scope.h"
#include "BaseScope.h"

#include <string>

struct GlobalScope : BaseScope
{
  GlobalScope(ScopePtr enclosingScope) :
    BaseScope(enclosingScope)
  {}

  std::string getScopeName() const override
  {
    return "globals";
  }
};

