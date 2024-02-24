#pragma once

#include "DefaultErrorStrategy.h"
#include "InputMismatchException.h"

struct BailingErrorStrategy : antlr4::DefaultErrorStrategy
{
  void recover(antlr4::Parser* recognizer,
               std::exception_ptr e) override
  {
    //rethrow RecognitionException wrapped in a generic 
    //std::exception so that is not caught by rule functions.
    try
    {
      std::rethrow_exception(e);
    }
    catch (std::exception const& ex)
    {
      throw std::exception(ex);
    }
  }

  antlr4::Token* recoverInline(antlr4::Parser* recognizer) override
  {
    //don't attempt to recover inline
    throw std::exception(antlr4::InputMismatchException(recognizer));
  }

  void sync(antlr4::Parser* recognizer) override
  {
    //don't attempt to recover, we are bailing!
  }
};

