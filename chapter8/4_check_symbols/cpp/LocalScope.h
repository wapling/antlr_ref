#pragma once

#include "Scope.h"
#include "BaseScope.h"

#include <string>

struct LocalScope : BaseScope
{
  LocalScope(ScopePtr enclosingScope) :
    BaseScope(enclosingScope)
  {}

  std::string getScopeName() const override
  {
    return "locals";
  }
};

