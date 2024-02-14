#pragma once

#include "Symbol.h"

#include <string>

class VariableSymbol : public Symbol
{

public:

  VariableSymbol(std::string const& name,
                 Type retType) :
    Symbol(name, retType)
  {}

  SymbolType getSymbolType() const override
  {
    return VarSymbol;
  }
};
