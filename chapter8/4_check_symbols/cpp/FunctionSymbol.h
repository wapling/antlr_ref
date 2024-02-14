#pragma once

#include "Scope.h"
#include "Symbol.h"

#include <map>
#include <sstream>
#include <string>

class FunctionSymbol : public Symbol, public Scope
{
  std::map<std::string, SymbolPtr> arguments_;
  ScopePtr enclosingScope_;

public:

  FunctionSymbol(std::string const& name,
                 Type retType,
                 ScopePtr enclosingScope) :
    Symbol(name, retType),
    enclosingScope_(enclosingScope)
  {}

  SymbolType getSymbolType() const override
  {
    return FuncSymbol;
  }

  std::string getScopeName() const override
  {
    return getName();
  }

  ScopePtr getEnclosingScope() const override
  {
    return enclosingScope_;
  }

  void define(SymbolPtr sym) override
  {
    arguments_.insert({sym->getName(), sym});
    sym->setScope(shared_from_this());
  }

  SymbolPtr resolve(std::string const& name) const override
  {
    auto it = arguments_.find(name);
    if (it != arguments_.end())
      return it->second;

    ScopePtr enclosing = getEnclosingScope();
    if (enclosing)
      return enclosing->resolve(name);
    else
      return nullptr;
  }

  std::string toString() const override
  {
    std::ostringstream oss;

    oss << "function"
        << Symbol::toString()
        << ":[";
    bool first_time = true;
    for (auto it : arguments_)
    {
      if (first_time)
        first_time = false;
      else
        oss << ", ";
      oss << it.second->toString();
    } 
    oss << ']';
    return oss.str();
  }
};
