grammar Tags;

file  : (TAG|ENTITY|TEXT|CDATA)+ ;

COMMENT : '<!--' .*? '-->' -> skip ;
CDATA   : '<![CDATA[' .*? ']]>' ;
TAG     : '<' .*? '>' ;
ENTITY  : '&' .*? ';' ;
TEXT    : ~[<&]+ ;

