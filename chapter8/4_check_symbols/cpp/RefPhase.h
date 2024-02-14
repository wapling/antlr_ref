#pragma once

#include "Symbol.h"

#include "CymbolBaseListener.h"

#include "tree/ParseTree.h"
#include "tree/ParseTreeProperty.h"

#include <string>

class RefPhase : public CymbolBaseListener
{
  antlr4::tree::ParseTreeProperty<ScopePtr>& scopes_;
  ScopePtr globals_;
  ScopePtr currentScope_;

public:

  RefPhase(ScopePtr globals, antlr4::tree::ParseTreeProperty<ScopePtr>& scopes) :
    scopes_(scopes),
    globals_(globals)
  {}

  void enterFile(CymbolParser::FileContext * ctx) override
  {
    currentScope_ = globals_;
  }

  void enterFunctionDecl(CymbolParser::FunctionDeclContext * ctx) override
  {
    currentScope_ = scopes_.get(ctx);
  }

  void exitFunctionDecl(CymbolParser::FunctionDeclContext * ctx) override
  {
    currentScope_ = currentScope_->getEnclosingScope();
  }

  void enterBlock(CymbolParser::BlockContext * ctx) override
  {
    currentScope_ = scopes_.get(ctx);
  }

  void exitBlock(CymbolParser::BlockContext * ctx) override
  {
    currentScope_ = currentScope_->getEnclosingScope();
  }

  void exitVar(CymbolParser::VarContext * ctx) override
  {
    std::string name = ctx->ID()->getSymbol()->getText();
    SymbolPtr variable = currentScope_->resolve(name);
    if (!variable)
    {
      error_message(ctx->ID()->getSymbol(),
                    std::string("No such variable: ") + name);
    }
    else if (variable->getSymbolType() == Symbol::FuncSymbol)
    {
      error_message(ctx->ID()->getSymbol(),
                    name + " is not a variable.");
    }
  }

  void exitCall(CymbolParser::CallContext * ctx) override
  {
    std::string name = ctx->ID()->getSymbol()->getText();
    SymbolPtr function = currentScope_->resolve(name);
    if (!function)
    {
      error_message(ctx->ID()->getSymbol(),
                    std::string("No such function: ") + name);
    }
    else if (function->getSymbolType() == Symbol::VarSymbol)
    {
      error_message(ctx->ID()->getSymbol(),
                    name + " is not a function.");
    }
  }


};

