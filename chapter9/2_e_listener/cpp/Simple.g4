grammar Simple;

prog: classDef+ ;             // match multiple class definitions

classDef
  : 'class' ID '{' member+ '}' ;

member
  : 'int' ID ';'                        #fieldDef
  | 'int' f=ID '(' ID ')' '{' stat '}'  #methodDef
  ;

stat
  : expr ';'                            #statExpr
  | ID '=' expr ';'                     #statAssign
  ;

expr
  : INT
  | ID '(' INT ')'
  ;

INT : [0-9]+ ;
ID  : [a-zA-Z]+ ;
WS  : [ \t\r\n]+ -> skip ;


