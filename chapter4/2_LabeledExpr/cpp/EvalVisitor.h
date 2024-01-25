#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include "LabeledExprBaseVisitor.h"

class EvalVisitor : public LabeledExprBaseVisitor
{
  std::unordered_map<std::string, int> memory_;

public:

  std::any visitAssign(LabeledExprParser::AssignContext *ctx) override 
  {
    std::string id = ctx->ID()->getText();
    int value = std::any_cast<int>(visit(ctx->expr()));
    memory_.insert_or_assign(id, value);
    return value;
  }

  std::any visitClear(LabeledExprParser::ClearContext *ctx) override
  {
    memory_.clear();
    return 0;
  }

  std::any visitPrintExpr(LabeledExprParser::PrintExprContext *ctx) override 
  {
    int value = std::any_cast<int>(visit(ctx->expr()));
    std::cout << value << std::endl;
    return 0;
  }

  std::any visitInt(LabeledExprParser::IntContext *ctx) override
  {
    return std::stoi(ctx->INT()->getText());
  }

  std::any visitId(LabeledExprParser::IdContext *ctx) override
  {
    auto const& value = memory_.find(ctx->ID()->getText());
    if (value == memory_.end())
      return 0;
    return value->second;
  }

  std::any visitMultDiv(LabeledExprParser::MultDivContext *ctx) override
  {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    if (ctx->op->getType() == LabeledExprParser::MUL)
      return left * right;
    else
      return left / right;
  }

  std::any visitAddSub(LabeledExprParser::AddSubContext *ctx) override
  {
    int left = std::any_cast<int>(visit(ctx->expr(0)));
    int right = std::any_cast<int>(visit(ctx->expr(1)));
    if (ctx->op->getType() == LabeledExprParser::ADD)
      return left + right;
    else
      return left - right;
  }

  std::any visitParens(LabeledExprParser::ParensContext *ctx) override
  {
    return visit(ctx->expr());
  }



};

