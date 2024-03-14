grammar Enum;

@parser::members { bool java5 = false; }

@parser::header {
#ifndef ENUM_HEADER_
#define ENUM_HEADER_

#include <iostream>

#endif
}

prog  : (stat | enumDecl)+ ;

stat  : id '=' expr ';'
        { 
          std::cout << $id.text << "=" << $expr.text << std::endl; 
        } 
      ;

expr  : id
      | INT
      ;

enumDecl
  : {java5}? 'enum' name=id '{' id ( ',' id )* '}' 
    {
      std::cout << "enum " << $name.text << std::endl;
    }
  ;

id  : ID
    | {!java5}? 'enum'
    ;

ID  : [a-zA-Z]+ ;
INT : [0-9]+ ;
WS  : [ \t\n\r]+ -> skip ;

