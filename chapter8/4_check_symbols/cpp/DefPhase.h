#pragma once

#include "GlobalScope.h"
#include "LocalScope.h"
#include "Symbol.h"
#include "SymbolUtils.h"
#include "FunctionSymbol.h"
#include "VariableSymbol.h"

#include "CymbolBaseListener.h"

#include "tree/ParseTree.h"
#include "tree/ParseTreeProperty.h"

#include <memory>
#include <string>

class DefPhase : public CymbolBaseListener
{
  antlr4::tree::ParseTreeProperty<ScopePtr> scopes_;
  ScopePtr globals_;
  ScopePtr currentScope_;

public:
  
  antlr4::tree::ParseTreeProperty<ScopePtr>& getScopes()
  {
    return scopes_;
  }

  ScopePtr getGlobals()
  {
    return globals_;
  }

  void enterFile(CymbolParser::FileContext * ctx) override
  {
    globals_ = std::make_shared<GlobalScope>(nullptr);
    currentScope_ = globals_;
  }

  void exitFile(CymbolParser::FileContext * ctx) override
  {
    std::cout << globals_->toString() << '\n';
  }

  void enterFunctionDecl(CymbolParser::FunctionDeclContext * ctx) override
  {
    std::string name = ctx->ID()->getText();
    int typeTokenType = ctx->type()->start->getType();
    Symbol::Type type = getType(typeTokenType);

    SymbolPtr function =
      std::make_shared<FunctionSymbol>(name, type, currentScope_);
    currentScope_->define(function);
    currentScope_ = std::dynamic_pointer_cast<Scope>(function);
    scopes_.put(ctx, currentScope_);
  }

  void exitFunctionDecl(CymbolParser::FunctionDeclContext * ctx) override
  {
    std::cout << currentScope_->toString() << '\n';
    currentScope_ = currentScope_->getEnclosingScope();
  }

  void enterBlock(CymbolParser::BlockContext * ctx) override
  {
    currentScope_ = std::make_shared<LocalScope>(currentScope_);
    scopes_.put(ctx, currentScope_);
  }

  void exitBlock(CymbolParser::BlockContext * ctx) override
  {
    std::cout << currentScope_->toString() << '\n';
    currentScope_ = currentScope_->getEnclosingScope();
  }

  void exitFormalParameter(CymbolParser::FormalParameterContext * ctx) override
  {
    defineVar(ctx->type(), ctx->ID()->getSymbol());
  }

  void exitVarDecl(CymbolParser::VarDeclContext * ctx) override
  {
    defineVar(ctx->type(), ctx->ID()->getSymbol());
  }

  void defineVar(CymbolParser::TypeContext* typeCtx, antlr4::Token* token)
  {
    int typeTokenType = typeCtx->start->getType();
    Symbol::Type type = getType(typeTokenType);
    SymbolPtr varSym = std::make_shared<VariableSymbol>(token->getText(), type);
    currentScope_->define(varSym);
  }
};

