#pragma once

#include "Scope.h"

#include <memory>
#include <ostream>
#include <sstream>
#include <string>

struct Symbol
{
  enum Type {tINVALID, tVOID, tINT, tFLOAT};
  enum SymbolType {VarSymbol, FuncSymbol};
 
  virtual ~Symbol() = default;

  Symbol(std::string const& name) :
    name_(name)
  {}

  Symbol(std::string const& name, Type type) :
    name_(name),
    type_(type)
  {}

  std::string const& getName() const
  {
    return name_;
  }

  virtual SymbolType getSymbolType() const = 0;

  std::string toString() const;

  ScopePtr getScope() const
  {
    return scope_;
  }

  void setScope(ScopePtr scope)
  {
    scope_ = scope;
  }

private:
  std::string name_;
  Type        type_;
  ScopePtr    scope_; 
};

typedef std::shared_ptr<Symbol> SymbolPtr;

std::ostream& operator<<(std::ostream& ostrm, Symbol::Type type);

