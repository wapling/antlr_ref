#pragma once

#include "CymbolBaseListener.h"

#include "BufferedTokenStream.h"
#include "TokenStreamRewriter.h"

#include <string>
#include <vector>

namespace
{
  inline std::string trim(std::string s)
  {
    if (s.empty())
      return s;

    while (!s.empty() && std::isspace(*s.begin()))
      s = s.substr(1);

    while (!s.empty() && std::isspace(*s.rbegin()))
      s = s.substr(0, s.length() - 1);

    return s;
  }
}

struct CommentShifter : CymbolBaseListener
{
  antlr4::BufferedTokenStream* tokens_;
  antlr4::TokenStreamRewriter rewriter_;

  CommentShifter(antlr4::BufferedTokenStream* tokens) :
    tokens_(tokens),
    rewriter_(tokens_)
  {}

  void exitVarDecl(CymbolParser::VarDeclContext * ctx) override
  { 
    antlr4::Token* semi = ctx->getStop();
    int i = semi->getTokenIndex();
    std::vector<antlr4::Token *> cmtChannel = tokens_->getHiddenTokensToRight(i, 2);
    if (!cmtChannel.empty())
    {
      antlr4::Token* cmt = *cmtChannel.begin();
      if (cmt)
      {
        std::string txt = cmt->getText().substr(2);
        std::string newCmt = "/*" + trim(txt) + "*/\n";
        rewriter_.insertBefore(ctx->start, newCmt);
        rewriter_.replace(cmt, "\n");
      }
    }
  }


};

