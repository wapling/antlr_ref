#pragma once

#include "VecMsgBaseListener.h"
#include "VecMsgParser.h"

#include "Token.h"

#include <sstream>

struct TestVecMsgListener : VecMsgBaseListener
{
  TestVecMsgListener(VecMsgParser* parser, int max_count) :
    parser_(parser),
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
      std::ostringstream oss;
      antlr4::Token* token = ctx->INT()->getSymbol();
      oss << "Line: " << token->getLine()
          << ':' << token->getStartIndex()
          << " rule ints exceeded max " << max_count_;
      parser_->notifyErrorListeners(oss.str());
    }
  }

private:
  VecMsgParser* parser_;
  int count_;
  int max_count_;
};

