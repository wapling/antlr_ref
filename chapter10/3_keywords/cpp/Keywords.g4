grammar Keywords;

@lexer::header {
#ifndef KEYWORDS_HEADER_
#define KEYWORDS_HEADER_

#include "KeywordsParser.h"

#include <iostream>
#include <unordered_map>
#include <string>

namespace {

struct Keywords
{
  std::unordered_map<std::string, int> data_;
  
  Keywords()
  {
    data_.insert_or_assign("begin", KeywordsParser::BEGIN);
    data_.insert_or_assign("end", KeywordsParser::END);
    data_.insert_or_assign("if", KeywordsParser::IF);
    data_.insert_or_assign("then", KeywordsParser::THEN);
    data_.insert_or_assign("while", KeywordsParser::WHILE);
  }

  bool contains_key(std::string const& key) const
  {
    return data_.find(key) != data_.end();
  }

  int get(std::string const& key)
  {
    return data_[key];
  }
};
} // anonymous namespace

#endif
}

@lexer::members {
Keywords keywords_;  
}


tokens {BEGIN, END, IF, THEN, WHILE}

stat
  : BEGIN stat* END
  | IF expr THEN stat
  | WHILE expr stat
  | ID '=' expr ';'
  ;

expr
  : INT
  | CHAR
  ;

ID  : [a-zA-Z]+
      {
        if (keywords_.contains_key(getText()))
          setType(keywords_.get(getText()));
      }
    ;

CHAR  : '\'' . '\''
      {
        setText(std::string(1, getText()[1]));
      }
      ;

INT   : [0-9]+ ;
WS    : [ \t\n\r]+ -> skip ;

