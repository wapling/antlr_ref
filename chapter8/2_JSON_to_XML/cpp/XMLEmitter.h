#pragma once

#include "JSONBaseListener.h"

#include "tree/ParseTree.h"
#include "tree/ParseTreeProperty.h"

#include <string>
#include <sstream>

namespace {

std::string stripQuotes(std::string const& s)
{
  if (s.empty() || s[0] != '"')
    return s;

  return s.substr(1, s.length() - 2);
}

std::string decorateWithRoot(std::string const& xml_fragment)
{
  return std::string("<?xml version='1.0'?><root>") + xml_fragment + "</root>";
}
 
} //anonymous namespace

class XMLEmitter : public JSONBaseListener
{

  antlr4::tree::ParseTreeProperty<std::string> xml_;

public:

  std::string getXML(antlr4::tree::ParseTree* ctx)
  {
    return xml_.get(ctx);
  }

  void setXML(antlr4::tree::ParseTree* ctx, std::string const& s)
  {
    xml_.put(ctx, s);
  }

  void exitAtom(JSONParser::AtomContext * ctx) override
  {
    setXML(ctx, ctx->getText());
  }

  void exitString(JSONParser::StringContext * ctx) override
  {
    setXML(ctx, stripQuotes(ctx->getText()));
  }

  void exitObjectValue(JSONParser::ObjectValueContext * ctx) override
  {
    setXML(ctx, getXML(ctx->object()));
  }

  void exitPair(JSONParser::PairContext * ctx) override
  {
    std::string tag = stripQuotes(ctx->STRING()->getText());
    JSONParser::ValueContext* vctx = ctx->value();
    std::ostringstream oss;
    oss << '<' << tag << '>'
        << getXML(vctx)
        << "</" << tag << '>';
    setXML(ctx, oss.str());
  }

  void exitAnObject(JSONParser::AnObjectContext * ctx) override
  {
    std::ostringstream oss;
    oss << '\n';
    for (JSONParser::PairContext* pctx : ctx->pair())
      oss << getXML(pctx);
    setXML(ctx, oss.str());
  }

  void exitEmptyObject(JSONParser::EmptyObjectContext * ctx) override
  {
    setXML(ctx, "");
  }

  void exitArrayOfValues(JSONParser::ArrayOfValuesContext * ctx) override
  {
    std::ostringstream oss;
    oss << '\n';
    for (JSONParser::ValueContext* vctx : ctx->value())
      oss << "<element>" << getXML(vctx) << "</element>\n";
    setXML(ctx, oss.str());
  }

  void exitEmptyArray(JSONParser::EmptyArrayContext * ctx) override
  {
    setXML(ctx, "");
  }

  void exitJson(JSONParser::JsonContext * ctx) override
  {
    setXML(ctx, decorateWithRoot(getXML(ctx->children[0])));
  }


};

