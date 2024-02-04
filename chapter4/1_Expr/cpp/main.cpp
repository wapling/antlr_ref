#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "ExprLexer.h"
#include "ExprParser.h"

using namespace antlr4;
using antlr4::tree::ParseTree;

std::unique_ptr<CharStream> get_input_stream(int argc, char* argv[])
{
  if (argc > 1) 
  {
    std::unique_ptr<ANTLRFileStream> retval = std::make_unique<ANTLRFileStream>();
    retval->loadFromFile(argv[1]);
    return retval;
  }
  else
    return std::make_unique<ANTLRInputStream>(ANTLRInputStream(std::cin));
}

int main(int argc, char* argv[])
{
  try
  {
  
    if (argc > 2)
      throw std::runtime_error("Too many arguments");

    std::unique_ptr<CharStream> input = get_input_stream(argc, argv);

    ExprLexer lex(input.get());
    CommonTokenStream tokens(&lex);
    ExprParser parser(&tokens);
    ParseTree* tree = parser.prog();
    std::cout << tree->toStringTree(&parser) << std::endl;

  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



