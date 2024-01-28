grammar CSV;

file  : hdr row+ ;
hdr   : row ;
row   : field (',' field)* NL ;
field : TEXT
      | STRING
      | 
      ;


NL      : '\r'? '\n' ;
TEXT    : ~[,\n\r"]+ ;
STRING  : '"' ('""'|~'"')* '"' ;
