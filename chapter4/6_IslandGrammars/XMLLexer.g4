lexer grammar XMLLexer;

// Default - outside of tags
OPEN      : '<'             -> pushMode(INSIDE) ;
COMMENT   : '<!--' .*? '->' -> skip ;
EntityRef : '&' [a-z]+ ';' ;
TEXT      : ~('<'|'&')+ ;

// Mode inside of tags
mode INSIDE;

CLOSE       : '>'     -> popMode ;
SLASH_CLOSE : '/>'    -> popMode ;
EQUALS      : '=' ;
STRING      : '"' .*? '"' ;
SlashName   : '/' Name ;
Name        : ALPHA (ALPHA|DIGIT)* ;
S           : [ \t\r\n]+ -> skip ;

fragment
ALPHA       : [a-zA-Z] ;

fragment
DIGIT       : [0-9] ;

