grammar Call;

stat  : fcall ';' ;

fcall
  : ID '(' expr ')'       # legal_fcall
  | ID '(' expr ')' ')'+  # extra_paren
  | ID '(' expr           # missing_paren
  ;

expr
  : '(' expr ')'
  | INT
  ;

ID  : [a-zA-Z]+ ;
INT : [0-9]+ ;
WS  : [ \n\r\t]+ -> skip ;
