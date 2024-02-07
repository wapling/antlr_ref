#pragma once

#include "LExprBaseListener.h"

#include "tree/ParseTree.h"
#include "tree/ParseTreeProperty.h"

#include <string>

class EvaluatorWithProps : public LExprBaseListener
{

  antlr4::tree::ParseTreeProperty<int> values_;

public:

  void setValue(antlr4::tree::ParseTree* node, int value)
  {
    values_.put(node, value);
  }

  int getValue(antlr4::tree::ParseTree* node)
  {
    return values_.get(node);
  }

  void exitAdd(LExprParser::AddContext * ctx) override
  {
    int lhs = getValue(ctx->e(0));
    int rhs = getValue(ctx->e(1));
    setValue(ctx, lhs + rhs);
  }

  void exitMult(LExprParser::MultContext * ctx) override
  {
    int lhs = getValue(ctx->e(0));
    int rhs = getValue(ctx->e(1));
    setValue(ctx, lhs * rhs);
  }

  void exitInt(LExprParser::IntContext * ctx) override
  {
    setValue(ctx, std::stoi(ctx->INT()->getText()));
  }

  void exitS(LExprParser::SContext * ctx) override
  {
    setValue(ctx, getValue(ctx->e()));
  }
};

