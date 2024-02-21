grammar Ambig;

stat  : expr ';'
      | ID '(' ')' ';'
      ;

expr  : ID '(' ')'
      | INT
      ;

INT   : [0-9]+ ;
ID    : [a-zA-Z]+ ;
WS    : [ \t\r\n]+ -> skip ;

