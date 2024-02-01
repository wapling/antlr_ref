#pragma once

#include "PropertyFileBaseListener.h"

#include <map>
#include <string>

class PropertyFileLoader : public PropertyFileBaseListener
{
  std::map<std::string, std::string> props_;

public:

  void exitProp(PropertyFileParser::PropContext * ctx) override
  {
    std::string id = ctx->ID()->getText();
    std::string value = ctx->STRING()->getText();
    props_.insert_or_assign(id, value);
  }

  std::map<std::string, std::string> const& getProps() const
  {
    return props_;
  }
};

