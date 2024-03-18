lexer grammar ModeTagsLexer;

OPEN  : '<' -> mode(ISLAND) ;
TEXT  : ~'<'+ ;

mode ISLAND;
CLOSE : '>' -> mode(DEFAULT_MODE) ;
SLASH : '/' ;
ID    : [a-zA-Z]+ ;

