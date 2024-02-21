#pragma once

#include "AmbigBaseListener.h"

#include <iostream>

struct AmbigErrorListener : AmbigBaseListener
{
  void exitStat(AmbigParser::StatContext * ctx) override
  {
    std::cout << "stat: " << ctx->ID()->getText() << '\n';
  }

  void exitExpr(AmbigParser::ExprContext * ctx) override
  {
    std::cout << "expr: " << ctx->ID()->getText() << '\n';
  }
};

