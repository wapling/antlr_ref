#pragma once

#include "LExprBaseListener.h"

#include <stack>
#include <string>

class Evaluator : public LExprBaseListener
{
  std::stack<int> stack_;

public:

  void exitAdd(LExprParser::AddContext *) override
  {
    int rhs = stack_.top();
    stack_.pop();
    int lhs = stack_.top();
    stack_.pop();
    stack_.push(lhs + rhs);
  }

  void exitMult(LExprParser::MultContext *) override
  {
    int rhs = stack_.top();
    stack_.pop();
    int lhs = stack_.top();
    stack_.pop();
    stack_.push(lhs * rhs);
  }

  void exitInt(LExprParser::IntContext * ctx) override
  {
    stack_.push(std::stoi(ctx->INT()->getText()));
  }

  int getTop() const
  {
    return stack_.top();
  }
};

