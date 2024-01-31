grammar R;

prog            : ( expr_or_assign (';' | NL)+ | NL )* EOF
                ;

expr_or_assign  : expr ('<-' | '=' | '<<-') expr_or_assign
                | expr
                ;

expr            : '[[' sub_list ']' ']'
                | '[' sub_list ']'
                | expr ('::' | ':::') expr 
                | expr ('$' | '@') expr
                | <assoc=right> expr '^' expr
                | ('-' | '+') expr
                | expr ':' expr
                | expr USER_OP expr                     //anything wrapped in %: '%' .* '%'
                | expr ('*' | '/') expr
                | expr ('+' | '-') expr
                | expr ('>' | '>=' | '<' | '<=' | '==' | '!=') expr
                | '!' expr
                | expr ('&' | '&&') expr
                | expr ('|' | '||') expr
                | '~' expr
                | expr '~' expr
                | expr ('->' | '->>' | ':=') expr
                | 'function' '(' form_list? ')' expr    //function definition
                | expr '(' sub_list ')'                 //call function
                | '{' expr_list '}'                     //compound statement
                | 'if' '(' expr ')' expr
                | 'if' '(' expr ')' expr 'else' expr
                | 'for' '(' ID 'in' expr ')' expr
                | 'while' '(' expr ')' expr
                | 'repeat' expr
                | '?' expr
                | 'next'
                | 'break'
                |   ID
                |   STRING
                |   INT
                ;

expr_list       : expr_or_assign ((';' | NL) expr_or_assign)* ;

form_list       : form (',' form)* ;

form            : ID
                | ID '=' expr
                | '...'
                ;

sub_list        : sub (',' sub)* ;

sub             : expr
                | ID '='
                | ID '=' expr
                | STRING '='
                | STRING '=' expr
                | 'NULL' '='
                | 'NULL' '=' expr
                | '...'
                | 
                ;

ID      : '.' (LETTER | '_' | '.') (LETTER | DIGIT | '_' | '.')*
        | LETTER (LETTER | DIGIT | '_' | '.')*
        ;

INT :   DIGIT+ [Ll]? ;

fragment LETTER : [a-zA-Z] ;
fragment DIGIT  : [0-9] ;

STRING
    :   '"' ( ESC | ~[\\"] )*? '"'
    |   '\'' ( ESC | ~[\\'] )*? '\''
    ;

fragment ESC :   '\\' ([abtnfrv]|'"'|'\'') ;

USER_OP :   '%' .*? '%' ;

NL      : '\r'? '\n' ;
WS      :   [ \t]+ -> skip ;

