#pragma once

#include "VecMsgBaseListener.h"

#include "Token.h"

#include <iostream>

struct TestVecMsgListener : VecMsgBaseListener
{
  TestVecMsgListener(int max_count) :
    count_(0),
    max_count_(max_count)
  {}

  void exitFirst_int(VecMsgParser::First_intContext * ctx) override
  {
    count_ = 1;
  }

  void exitNext_int(VecMsgParser::Next_intContext * ctx) override
  {
    ++count_;
    if (count_>max_count_)
    {
      antlr4::Token* token = ctx->INT()->getSymbol();
      std::cerr << "Line: " << token->getLine()
                << ':' << token->getStartIndex()
                << " rule ints exceeded max " << max_count_
                << '\n';
    }
  }

private:
  int count_;
  int max_count_;
};

