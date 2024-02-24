grammar Call;

stat  : fcall ';' ;

fcall
  : ID '(' expr ')'
  | ID '(' expr ')' ')'   {notifyErrorListeners("Too many parentheses");}
  | ID '(' expr           {notifyErrorListeners("Missing closing parenthesis");}
  ;

expr
  : '(' expr ')'
  | INT
  ;

ID  : [a-zA-Z]+ ;
INT : [0-9]+ ;
WS  : [ \n\r\t]+ -> skip ;
