#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "SimpleLexer.h"
#include "SimpleParser.h"

#include "SimpleErrorListener.h"
#include "VerboseErrorListener.h"
#include "UnderlineErrorListener.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace antlr4;
using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeWalker;

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
  
    if (argc > 3)
      throw std::runtime_error("Too many arguments");

    std::unique_ptr<CharStream> input = get_input_stream(argc, argv);

    SimpleLexer lex(input.get());
    CommonTokenStream tokens(&lex);
    SimpleParser parser(&tokens);
    parser.removeErrorListeners();
//    VerboseErrorListener vl;
//    parser.addErrorListener(&vl);
    UnderlineErrorListener ul;
    parser.addErrorListener(&ul);
    ParseTree* tree = parser.prog();
    ParseTreeWalker walker;
    SimpleErrorListener listener;
    walker.walk(&listener, tree);

  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



