grammar LabeledExpr;

prog  : stat+ ;

stat  : expr NEWLINE            # printExpr
      | ID '=' expr NEWLINE     # assign
      | NEWLINE                 # blank
      | CLEAR                   # clear
      ;

expr  : expr op=('*'|'/') expr  # MultDiv
      | expr op=('+'|'-') expr  # AddSub
      | INT                     # int
      | ID                      # id
      | '(' expr ')'            # parens
      ;

CLEAR     : 'clear' ;
MUL       : '*' ;
DIV       : '/' ;
ADD       : '+' ;
SUB       : '-' ;
ID        : [a-zA-Z]+ ;
INT       : [0-9]+ ;
NEWLINE   : '\r'? '\n' ;
WS        : [ \t]+ -> skip ;

