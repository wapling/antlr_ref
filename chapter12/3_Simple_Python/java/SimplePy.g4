grammar SimplePy;

@lexer::members {
  int nesting = 0;
}

file  : stat+ EOF ;

stat  : assign NEWLINE
      | expr NEWLINE
      | NEWLINE
      ;

assign  : ID '=' expr ;

expr  : expr '+' expr
      | LPAREN expr RPAREN
      | call
      | list
      | ID
      | INT
      ;

call  : ID LPAREN (expr (',' expr)* )? RPAREN ;

list  : LBRACK (expr (',' expr)* )? RBRACK ;

LBRACK  : '[' {nesting++;} ;

RBRACK  : ']' {nesting--;} ;

LPAREN  : '(' {nesting++;} ;

RPAREN  : ')' {nesting--;} ;

INT : [0-9]+ ;
ID  : [a-zA-Z_][a-zA-Z_0-9]* ;

IGNORE_NEWLINE  : '\r'? '\n' {nesting > 0}? -> skip ;
NEWLINE : '\r'? '\n' {nesting == 0}? ;

WS      : [ \t]+ -> skip ;

COMMENT : '#' ~[\r\n]* -> skip ;

LINE_ESCAPE : '\\' '\r'? '\n' -> skip ;

