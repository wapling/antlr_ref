grammar Cymbol;

file : stat+ ;

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
      | functionDecl
      | 'if' expr 'then' stat ('else' stat)?
      | 'return' expr? ';'
      | expr '=' expr ';'
      | expr ';'
      ;

expr  : ID '(' exprList? ')'  #Call
      | ID '[' expr ']'       #Index
      | '-' expr              #Negate
      | '!' expr              #Not
      | expr '*' expr         #Mult
      | expr ('+'|'-') expr   #AddSub
      | expr '==' expr        #Equal
      | ID                    #Var
      | INT                   #Int
      | '(' expr ')'          #Parens
      ;

exprList : expr (',' expr)* ;

K_FLOAT : 'float';
K_INT   : 'int';
K_VOID  : 'void';
ID      : LETTER (LETTER | DIGIT)* ;
INT     : DIGIT+ ;
WS      : [ \t\r\n]+ -> skip ;

SL_COMMENT
    :   '//' .*? '\n' -> skip
    ;

fragment
LETTER  : [a-zA-Z] ;
fragment
DIGIT   : [0-9] ;

