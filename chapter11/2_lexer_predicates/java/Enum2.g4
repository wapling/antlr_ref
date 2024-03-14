grammar Enum2;

@lexer::members {public static boolean java5; }

prog  : (stat | enumDecl)+ ;

stat  : ID '=' expr ';' { System.out.println($ID.text + "=" + $expr.text); } ;

expr  : ID
      | INT
      ;

enumDecl
  : 'enum' name=ID '{' ID ( ',' ID )* '}' 
    { System.out.println("enum " + $name.text); }
  ;

ENUM  : 'enum' {java5}? ;
ID    : [a-zA-Z]+ ;
INT   : [0-9]+ ;
WS    : [ \t\n\r]+ -> skip ;
    
