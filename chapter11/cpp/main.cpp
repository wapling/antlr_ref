#include "CharStream.h"
#include "CommonTokenStream.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "EnumLexer.h"
#include "EnumParser.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace antlr4;

std::unique_ptr<CharStream> get_input_stream(std::string const& filename)
{
  if (!filename.empty()) 
  {
    std::unique_ptr<ANTLRFileStream> retval = std::make_unique<ANTLRFileStream>();
    retval->loadFromFile(filename);
    return retval;
  }
  else
    return std::make_unique<ANTLRInputStream>(ANTLRInputStream(std::cin));
}

bool is_java5(std::vector<std::string> const& args)
{
  for (auto const& arg : args)
    if (arg == "-java5")
      return true;
  return false;
}

std::string get_filename(std::vector<std::string> const& args)
{
  for (auto const& arg : args)
    if (arg != "-java5")
      return arg;
  return "";
}

int main(int argc, char* argv[])
{
  try
  {
  
    if (argc > 3)
      throw std::runtime_error("Too many arguments");
    
    std::vector<std::string> args(argv+1, argv+argc);
    bool java5 = is_java5(args);
    std::string filename = get_filename(args);
 
    std::unique_ptr<CharStream> input = get_input_stream(filename);

    EnumLexer lex(input.get());
    CommonTokenStream tokens(&lex);
    EnumParser parser(&tokens);

    parser.java5 = java5;;
    parser.prog();
  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



