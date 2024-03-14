grammar Enum2;

@lexer::members { bool java5 = false; }

@parser::header {
#ifndef ENUM_HEADER_
#define ENUM_HEADER_

#include <iostream>

#endif
}

prog  : (stat | enumDecl)+ ;

stat  : ID '=' expr ';'
        { 
          std::cout << $ID.text << "=" << $expr.text << std::endl; 
        } 
      ;

expr  : ID
      | INT
      ;

enumDecl
  : 'enum' name=ID '{' ID ( ',' ID )* '}' 
    {
      std::cout << "enum " << $name.text << std::endl;
    }
  ;

ENUM  : 'enum' {java5}? ;
ID    : [a-zA-Z]+ ;
INT   : [0-9]+ ;
WS    : [ \t\n\r]+ -> skip ;

