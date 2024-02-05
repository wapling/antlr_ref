#pragma once

#include "CSVBaseListener.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

class Loader : public CSVBaseListener
{
  std::vector<std::map<std::string, std::string>> rows_;
  std::vector<std::string> header_;
  std::vector<std::string> currentRowValues_;


public:

  void exitHdr(CSVParser::HdrContext *) override
  {
    header_ = std::move(currentRowValues_);
  }

  void enterRow(CSVParser::RowContext *) override
  {
    currentRowValues_.clear();
  }

  void exitRow(CSVParser::RowContext * ctx) override
  {
    if (ctx->getRuleIndex() == CSVParser::RuleHdr)
      return;

    std::map<std::string, std::string> new_row;
    std::size_t len = std::min(currentRowValues_.size(), header_.size());
    for (int i = 0; i < len; ++i)
      new_row.emplace(header_[i], currentRowValues_[i]);
    rows_.emplace_back(new_row);
  }

  void exitText(CSVParser::TextContext * ctx) override
  {
    currentRowValues_.push_back(ctx->TEXT()->getText());
  }

  void exitString(CSVParser::StringContext * ctx) override
  {
    currentRowValues_.push_back(ctx->STRING()->getText());
  }

  void exitEmpty(CSVParser::EmptyContext *) override
  {
    currentRowValues_.push_back("");
  }

  std::vector<std::map<std::string, std::string>> const& getData() const
  {
    return rows_;
  }
};

