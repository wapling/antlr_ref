#pragma once

#include "Scope.h"
#include "Symbol.h"

#include <map>
#include <sstream>
#include <string>

class BaseScope : public Scope
{
  std::map<std::string, SymbolPtr> symbols_;
  ScopePtr enclosingScope_;
  
public:

  BaseScope(ScopePtr enclosingScope) :
    enclosingScope_(enclosingScope)
  {}

  ScopePtr getEnclosingScope() const override
  {
    return enclosingScope_;
  }

  void define(SymbolPtr sym) override
  {
    symbols_.insert({sym->getName(), sym});
    sym->setScope(shared_from_this());
  }

  SymbolPtr resolve(std::string const& name) const override
  {
    auto it = symbols_.find(name);
    if (it != symbols_.end())
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

    oss << getScopeName()
        << ":[";
    bool first_time = true;
    for (auto it : symbols_)
    {
      if (first_time)
        first_time = false;
      else
        oss << ", ";
      oss << it.first;
    } 
    oss << ']';
    return oss.str();
  }
  
};
