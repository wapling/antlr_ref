#pragma once

#include "LExprBaseVisitor.h"

#include <string>

struct EvalVisitor : public LExprBaseVisitor
{

  std::any visitAdd(LExprParser::AddContext *ctx) override
  {
    return std::any_cast<int>(visit(ctx->e(0))) +
           std::any_cast<int>(visit(ctx->e(1)));
  }

  std::any visitMult(LExprParser::MultContext *ctx) override
  {
    return std::any_cast<int>(visit(ctx->e(0))) *
           std::any_cast<int>(visit(ctx->e(1)));
  }

  std::any visitInt(LExprParser::IntContext *ctx) override
  {
    return std::stoi(ctx->INT()->getText());
  }

};

