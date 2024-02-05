#include "antlr4-common.h"
#include "CharStream.h"
#include "CommonTokenStream.h"
#include "tree/ParseTree.h"
#include "ANTLRFileStream.h"
#include "ANTLRInputStream.h"

#include "CSVLexer.h"
#include "CSVParser.h"

#include "Loader.h"

#include <fstream>
#include <iostream>
#include <ostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <vector>

using namespace antlr4;
using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeWalker;

template <typename K, typename V>
std::ostream& operator<<(std::ostream& ostrm, std::map<K, V> const& data)
{
  ostrm << '{';
  bool first_time = true;
  for (auto const& datum : data)
  {
    if (first_time)
      first_time = false;
    else
      ostrm << ", ";
    ostrm << datum.first << ": " << datum.second;
  }
  ostrm << '}';
  return ostrm;
}

template <typename T>
std::ostream& operator<<(std::ostream& ostrm, std::vector<T> const& data)
{
  ostrm << '[';
  bool first_time = true;
  for (auto const& datum : data)
  {
    if (first_time)
      first_time = false;
    else
      ostrm << ", ";
    ostrm << datum;
  }
  ostrm << ']';
  return ostrm;
}

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

    CSVLexer lex(input.get());
    CommonTokenStream tokens(&lex);
    CSVParser parser(&tokens);
    ParseTree* tree = parser.file();
    ParseTreeWalker walker;
    Loader loader;
    walker.walk(&loader, tree);
    std::cout << loader.getData() << std::endl;

  }
  catch (std::exception const& ex)
  {
    std::cerr << "Error: " << ex.what() << '\n';
    return 1;
  }
}



