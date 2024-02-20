#pragma once

#include "BaseErrorListener.h"

#include "Parser.h"

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace
{
std::vector<std::string> split(std::string const& s, char seperator)
{
  std::vector<std::string> output;
  std::string::size_type prev_pos = 0, pos = 0;

  while((pos = s.find(seperator, pos)) != std::string::npos)
  {
      std::string substring( s.substr(prev_pos, pos-prev_pos) );

      output.push_back(substring);

      prev_pos = ++pos;
  }

  output.push_back(s.substr(prev_pos, pos - prev_pos));

  return output;
} 

} // anonymous namespace


struct UnderlineErrorListener : antlr4::BaseErrorListener
{
  void syntaxError(antlr4::Recognizer *recognizer,
                   antlr4::Token * offendingSymbol,
                   size_t line,
                   size_t charPositionInLine,
                   const std::string &msg,
                   std::exception_ptr e) override
  {
    std::cerr << "line " << line << ": " << charPositionInLine
              << ' ' << msg << '\n';
    underlineError(recognizer, offendingSymbol, line, charPositionInLine);
  }

protected:

  virtual void underlineError(antlr4::Recognizer *recognizer,
                              antlr4::Token * offendingToken,
                              size_t line,
                              size_t charPositionInLine)
  {
    antlr4::CommonTokenStream* tokens =
      dynamic_cast<antlr4::CommonTokenStream*>(recognizer->getInputStream());
    if (tokens)
    {
      std::string input = tokens->getTokenSource()->getInputStream()->toString();

      std::vector<std::string> lines = split(input, '\n');
      std::string error_line = lines[line - 1];
      size_t offendingTokenSize = offendingToken->getStopIndex() -
                                  offendingToken->getStartIndex() + 1;
      std::cerr << error_line << '\n'
                << std::string(charPositionInLine, ' ')
                << std::string(offendingTokenSize, '^')
                << '\n';
    }
    else
      std::cerr << "Unable to downcast IntStream* to CommonTokenStream*\n";
  }

};

