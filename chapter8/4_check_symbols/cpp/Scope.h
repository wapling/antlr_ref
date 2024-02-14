#pragma once

#include <memory>
#include <string>

struct Symbol;

typedef std::shared_ptr<Symbol> SymbolPtr;

struct Scope;

typedef std::shared_ptr<Scope> ScopePtr;

struct Scope : public std::enable_shared_from_this<Scope>
{
  virtual ~Scope() = default;

  virtual std::string getScopeName() const = 0;

  virtual ScopePtr getEnclosingScope() const = 0;

  virtual void define(SymbolPtr sym) = 0;

  virtual SymbolPtr resolve(std::string const& name) const = 0;

  virtual std::string toString() const = 0;
};

