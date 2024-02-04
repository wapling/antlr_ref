grammar LExpr;

s : e;
e : e op=MULT e   #mult 
  | e op=ADD e    #add
  | INT           #int
  ;

MULT: '*' ;
ADD : '+' ;
INT : [0-9]+ ;
WS : [ \t\n]+ -> skip ;

