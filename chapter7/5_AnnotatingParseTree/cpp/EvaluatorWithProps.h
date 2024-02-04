#pragma once

#include "LExprBaseListener.h"

#include "tree/ParseTree.h"
#include "tree/ParseTreeProperty.h"

#include <string>

using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeProperty;

class EvaluatorWithProps : public LExprBaseListener
{

  ParseTreeProperty<int> values_;

public:

  void setValue(ParseTree* node, int value)
  {
    values_.put(node, value);
  }

  int getValue(ParseTree* node)
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

