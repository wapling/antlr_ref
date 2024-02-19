#pragma once

#include "CymbolBaseListener.h"

#include <map>
#include <set>
#include <string>
#include <sstream>

class FunctionListener : public CymbolBaseListener
{

  std::set<std::string> nodes_;
  std::multimap<std::string, std::string> edges_;
  std::string currentFunction_;

  std::string getDotBoilerplatePrefix() const
  {
    return R"(
digraph G
{
  ranksep = .25;
  edge [arrowsize = .5]
  node [shape = circle, fontname = "ArialNarrow",
        fontsize = 12, fixedsize = true, height = .45];
)";
  }

  std::string getDotBoilerplatePostfix() const
  {
    return "}\n";
  }

public:

  virtual void enterFunctionDecl(CymbolParser::FunctionDeclContext * ctx) override
  {
    currentFunction_ = ctx->ID()->getText();
    nodes_.insert(currentFunction_);
  }

  virtual void exitCall(CymbolParser::CallContext * ctx) override
  {
    std::string callName = ctx->ID()->getText();
    edges_.insert({currentFunction_, callName});
  }

  std::string getDot() const
  {
    std::ostringstream oss;

    oss << getDotBoilerplatePrefix();

    for (auto const& node : nodes_)
      oss << node << "; ";

    for (auto const& node : nodes_)
    {
      auto range = edges_.equal_range(node);
      for (auto edge = range.first; edge != range.second; ++edge)
        oss << "   " << edge->first << " -> " << edge->second << ";\n";
    }

    oss << getDotBoilerplatePostfix();

    return oss.str();
  }
};

