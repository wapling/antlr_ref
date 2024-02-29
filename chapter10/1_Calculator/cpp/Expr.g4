grammar Expr;

@header {
#include <iostream>
#include <string>
#include <unordered_map>
}

@parser::members {
  std::unordered_map<std::string, int> memory_;
  
  int eval(int left, int op, int right)
  {
    switch (op)
    {
      case MUL: return left * right;
      case DIV: return left / right;
      case ADD: return left + right;
      case SUB: return left - right;
    }
    return 0;
  }
}

stat  : e NEWLINE         {std::cout << $e.v << '\n';}
      | ID '=' e NEWLINE  {memory_.insert_or_assign($ID.text, $e.v);}
      | NEWLINE
      ;

e returns [int v]
  : a=e op=('*'|'/') b=e  {$v = eval($a.v, $op.type, $b.v);}
  | a=e op=('+'|'-') b=e  {$v = eval($a.v, $op.type, $b.v);}
  | INT                   {$v = $INT.int;}
  | ID
    {
      std::string id = $ID.text;
      auto it = memory_.find(id);
      $v = memory_.end() != it ? it->second : 0;
    }
  | '('e ')'              {$v = $e.v;}
  ;

MUL : '*' ;
DIV : '/' ;
ADD : '+' ;
SUB : '-' ;

ID      : [a-zA-Z]+ ;
INT     : [0-9]+ ;
NEWLINE : '\r'? '\n' ;
WS      : [ \t]+ -> skip ;
 

