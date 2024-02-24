#pragma once

#include "CallBaseListener.h"
#include "CallParser.h"

#include "Token.h"

struct TestCallListener : CallBaseListener
{
  TestCallListener(CallParser* parser) :
    parser_(parser)
  {}

  void exitExtra_paren(CallParser::Extra_parenContext * ctx) override
  {
    parser_->notifyErrorListeners("Too many parentheses");
  }

  void exitMissing_paren(CallParser::Missing_parenContext * ctx) override
  {
    parser_->notifyErrorListeners("Missing closing parenthesis");
  }

private:
  CallParser* parser_;
};

