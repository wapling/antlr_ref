#pragma once

#include "SimpleLexer.h"

#include "CharStream.h"

#include <stdexcept>

struct BailSimpleLexer : SimpleLexer
{
  BailSimpleLexer(antlr4::CharStream* input) :
    SimpleLexer(input)
  {}

  void recover(antlr4::LexerNoViableAltException const& e) override
  {
    //rethrow LexerNoViableAltException wrapped in a 
    //generic std::exception so that is not caught by rule functions.
    throw std::exception(e);
  }
};

