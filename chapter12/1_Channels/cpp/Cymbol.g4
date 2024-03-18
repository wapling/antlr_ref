grammar Cymbol;

file:   (functionDecl | varDecl)+ ;

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

ID    : LETTER (LETTER | DIGIT)* ;
INT   : DIGIT+ ;

WS    : [ \t\r\n]+ -> channel(1) ;    // channel(WHITESPACE)

SL_COMMENT
    :   '//' .*? '\n' -> channel(2)   // channel(COMMENTS)
    ;

fragment
LETTER  : [a-zA-Z] ;
fragment
DIGIT   : [0-9] ;

