#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "ExprLexer.h"
#include "ExprParser.h"

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace antlr4;
using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeWalker;

int main(int argc, char* argv[])
{
  try
  {
    std::string expr;
    int line = 1;
 
    ExprParser parser(nullptr);
    parser.setBuildParseTree(false);

    while(std::getline(std::cin, expr))
    {
      ANTLRInputStream is(expr + '\n');
      ExprLexer lex(&is);
      lex.setLine(line);
      lex.setCharPositionInLine(0);
      CommonTokenStream tokens(&lex);
      parser.setInputStream(&tokens);
      parser.stat();
      ++line;
    }
  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



