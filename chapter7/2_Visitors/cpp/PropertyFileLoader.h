#pragma once

#include "PropertyFileBaseVisitor.h"

#include <map>
#include <string>

class PropertyFileLoader : public PropertyFileBaseVisitor
{
  std::map<std::string, std::string> props_;

public:

  std::any visitProp(PropertyFileParser::PropContext *ctx) override 
  {
    std::string id = ctx->ID()->getText();
    std::string value = ctx->STRING()->getText();
    props_.insert_or_assign(id, value);
    return std::any();
  }

  std::map<std::string, std::string> const& getProps() const
  {
    return props_;
  }
};

