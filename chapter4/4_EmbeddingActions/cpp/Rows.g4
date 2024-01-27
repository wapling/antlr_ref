grammar Rows;

@parser::members {

  int col_;

public:

  RowsParser(antlr4::TokenStream* input, int col) :
    RowsParser(input)
  {
    col_ = col;
  }
}

file: (row NL)+ ;

row
locals [int i=0]
  : (   STUFF
        {
          $i++;
          if ($i == col_) std::cout << $STUFF.text << '\n';
        }
    )+
  ;

TAB     : '\t' -> skip ;
NL      : '\r'? '\n' ;
STUFF   : ~[\t\r\n]+ ;

