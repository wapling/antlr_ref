#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "RowsLexer.h"
#include "RowsParser.h"

using namespace antlr4;
using antlr4::tree::ParseTree;


int main(int argc, char* argv[])
{
  try
  {
  
    if (argc != 2)
      throw std::runtime_error("Wrong arguments");

    ANTLRInputStream input(std::cin);
    RowsLexer lex(&input);
    CommonTokenStream tokens(&lex);
    int col = std::stoi(argv[1]);
    RowsParser parser = RowsParser(&tokens, col);
    parser.setBuildParseTree(false);
    parser.file();
  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



