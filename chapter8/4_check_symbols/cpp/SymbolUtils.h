#pragma once

#include "Symbol.h"

#include "CymbolParser.h"

#include "Token.h"

#include <iostream>
#include <string>

Symbol::Type getType(int tokenType)
{
  switch (tokenType)
  {
    case CymbolParser::K_VOID :  return Symbol::Type::tVOID;
    case CymbolParser::K_INT :   return Symbol::Type::tINT;
    case CymbolParser::K_FLOAT : return Symbol::Type::tFLOAT;
  }
  return Symbol::Type::tINVALID;
}

void error_message(antlr4::Token* token, std::string const& message)
{
  std::cerr << "line " << token->getLine() 
            << ':' << token->getCharPositionInLine()
            << ' ' << message << std::endl;
}

