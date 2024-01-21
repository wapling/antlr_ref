#include "ArrayInitBaseListener.h"
#include "RestoreIOState.h"

#include <iomanip>
#include <iostream>
#include <string>

class ShortToUnicodeString : public ArrayInitBaseListener
{
public:

  void enterInit(ArrayInitParser::InitContext *)  override
  {
    std::cout << '"';
  }

  void exitInit(ArrayInitParser::InitContext *) override
  { 
    std::cout << '"';
  }

  void enterValue(ArrayInitParser::ValueContext * ctx) override
  {
    int value = std::stoi(ctx->INT()->getText());
    RestoreIOState iostate(std::cout);
    std::cout << "|u" << std::hex << std::setw(4) << std::setfill('0') << value;
  }
};

