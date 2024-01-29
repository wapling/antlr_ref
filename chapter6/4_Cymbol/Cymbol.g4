grammar Cymbol;

file : (functionDecl | varDecl | stat)+ ;

varDecl
  : type ID ('=' expr)? ';'
  ;

type : 'float' | 'int' | 'void' ;

functionDecl
  : type ID '(' formalParameters? ')' block
  ;

formalParameters
  : formalParameter (',' formalParameter)* ;

formalParameter : type ID ;

block : '{' stat* '}' ;

stat  : block
      | varDecl
      | 'if' expr 'then' stat ('else' stat)?
      | 'return' expr? ';'
      | expr '=' expr ';'
      | expr ';'
      ;

expr  : ID '(' exprList? ')'
      | ID '[' expr ']'
      | '-' expr
      | '!' expr
      | expr '*' expr
      | expr ('+'|'-') expr
      | expr '==' expr
      | ID
      | INT
      | '(' expr ')'
      ;

exprList : expr (',' expr)* ;

ID    : LETTER (LETTER | DIGIT)* ;
INT   : DIGIT+ ;
WS    : [ \t\r\n]+ -> skip ;

SL_COMMENT
    :   '//' .*? '\n' -> skip
    ;

fragment
LETTER  : [a-zA-Z] ;
fragment
DIGIT   : [0-9] ;

