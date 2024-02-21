#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"
#include "DiagnosticErrorListener.h"
#include "atn/PredictionMode.h"
#include "atn/ParserATNSimulator.h"

#include "AmbigLexer.h"
#include "AmbigParser.h"

#include "AmbigErrorListener.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>

using namespace antlr4;
using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeWalker;
using antlr4::DiagnosticErrorListener;
using antlr4::atn::ParserATNSimulator;

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

    AmbigLexer lex(input.get());
    CommonTokenStream tokens(&lex);
    AmbigParser parser(&tokens);
    
    //parser.removeErrorListeners(); //this suppresses the diagnostics errors if executed
    DiagnosticErrorListener del;
    parser.addErrorListener(&del);
    parser.getInterpreter<ParserATNSimulator>()->setPredictionMode(
      antlr4::atn::PredictionMode::LL_EXACT_AMBIG_DETECTION);

    ParseTree* tree = parser.stat();
    ParseTreeWalker walker;
    AmbigErrorListener listener;
    walker.walk(&listener, tree);

  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



