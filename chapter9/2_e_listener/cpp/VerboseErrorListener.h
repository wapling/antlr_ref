#pragma once

#include "BaseErrorListener.h"

#include "Parser.h"

#include <iostream>
#include <string>
#include <vector>

struct VerboseErrorListener : antlr4::BaseErrorListener
{
  void syntaxError(antlr4::Recognizer *recognizer,
                   antlr4::Token * offendingSymbol,
                   size_t line,
                   size_t charPositionInLine,
                   const std::string &msg,
                   std::exception_ptr e) override
  {
    std::vector<std::string> stack = dynamic_cast<antlr4::Parser*>(recognizer)->getRuleInvocationStack();
    std::cerr << "rule stack: [";
    bool first_time = true;
    for (auto method = stack.rbegin(); method < stack.rend(); ++method)
    {
      if (first_time)
        first_time = false;
      else
        std::cerr << ", ";
      std::cerr << *method;
    }
    std::cerr << "]\n";

    std::cerr << "line " << line << ": " << charPositionInLine
              << " at " << offendingSymbol->toString() << ": " << msg << '\n';
  }
};

