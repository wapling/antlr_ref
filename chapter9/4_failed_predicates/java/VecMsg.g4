grammar VecMsg;

vec4  : '[' first_int (',' next_int)* ']' ;

first_int : INT ; 
next_int  : INT ;

INT : [0-9]+ ;
WS  : [ \n\r\t]+ -> skip ;

