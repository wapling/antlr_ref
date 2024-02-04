grammar Expr;

s : e;
e : e op=MULT e 
  | e op=ADD e
  | INT
  ;


