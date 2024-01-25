#pragma once

#include "JavaBaseListener.h"
#include "JavaParser.h"

#include <iostream>
#include <string>

class ExtractInterfaceListener : public JavaBaseListener
{
  JavaParser* parser_;

public:
  
  ExtractInterfaceListener(JavaParser* parser) :
    parser_(parser)
  {}

  void enterClassDeclaration(JavaParser::ClassDeclarationContext * ctx) override
  {
    std::cout << "interface I" << ctx->Identifier()->getSymbol()->getText() << "\n{\n";
  }

  void exitClassDeclaration(JavaParser::ClassDeclarationContext *) override
  {
    std::cout << "\n}\n";
  }

  void enterMethodDeclaration(JavaParser::MethodDeclarationContext * ctx) override
  {
    antlr4::TokenStream* tokens = parser_->getTokenStream();
    std::string type = ctx->type() ? tokens->getText(ctx->type()) : "void";
    std::string args = tokens->getText(ctx->formalParameters());
    std::cout << '\t' << type << ' ' << ctx->Identifier()->getSymbol()->getText() << args << '\n';
  }
};

