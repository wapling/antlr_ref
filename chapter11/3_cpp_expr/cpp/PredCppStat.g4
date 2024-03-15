grammar PredCppStat;

@parser::header {

#include "PredCppStatHeader.h"
 
}
@parser::members {

Types types;

bool istype() {
  return types.contains(getCurrentToken()->getText());
}

}

stat  : decl ';' { std::cout << "decl " << $decl.text << std::endl; }
      | expr ';' { std::cout << "expr " << $expr.text << std::endl; }
      ;

decl  : ID ID
      | {istype()}? ID '(' ID ')'
      ;

expr  : INT
      | ID
      | {!istype()}? ID '(' ID ')'
      ;


ID    : [a-zA-Z]+ ;
INT   : [0-9]+ ;
WS    : [ \t\n\r]+ -> skip ;
