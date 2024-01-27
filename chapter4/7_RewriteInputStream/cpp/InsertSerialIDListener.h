#pragma once

#include "JavaBaseListener.h"

#include "TokenStream.h"
#include "TokenStreamRewriter.h"

#include <iostream>
#include <string>

class InsertSerialIDListener : public JavaBaseListener
{
  antlr4::TokenStreamRewriter rewriter_;

public:
  
  InsertSerialIDListener(antlr4::TokenStream* tokens) :
    rewriter_(tokens)
  {}

  void enterClassBody(JavaParser::ClassBodyContext * ctx) override
  {
    std::string field = "\n\tpublic static final long serialVersionUID = 1L;";
    rewriter_.insertAfter(ctx->start, field);
  }

  antlr4::TokenStreamRewriter& getRewriter()
  {
    return rewriter_;
  }
};

