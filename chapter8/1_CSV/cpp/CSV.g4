grammar CSV;

file  : hdr row+ ;
hdr   : row ;
row   : field (',' field)* NL ;
field : TEXT          #text
      | STRING        #string
      |               #empty
      ;


NL      : '\r'? '\n' ;
TEXT    : ~[,\n\r"]+ ;
STRING  : '"' ('""'|~'"')* '"' ;
