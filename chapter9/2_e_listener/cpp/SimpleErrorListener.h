#pragma once

#include "SimpleBaseListener.h"

#include <iostream>

struct SimpleErrorListener : SimpleBaseListener
{
  void exitClassDef(SimpleParser::ClassDefContext * ctx) override
  {
    std::cout << "class: " << ctx->ID()->getText() << '\n';
  }

  void exitFieldDef(SimpleParser::FieldDefContext * ctx) override
  {
    std::cout << "var: " << ctx->ID()->getText() << '\n';
  }

  void exitMethodDef(SimpleParser::MethodDefContext * ctx) override
  {
    std::cout << "method: " << ctx->ID(0)->getText() << '\n';
  }

  void exitStatExpr(SimpleParser::StatExprContext * ctx) override
  {
    std::cout << "found expr: " << ctx->expr()->getText() << '\n';
  }

  void exitStatAssign(SimpleParser::StatAssignContext * ctx) override
  {
    std::cout << "found assign: " << ctx->expr()->getText() << '\n';
  }

};

