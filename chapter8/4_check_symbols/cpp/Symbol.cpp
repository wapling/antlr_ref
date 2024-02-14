#include "Symbol.h"

std::ostream& operator<<(std::ostream& ostrm, Symbol::Type type)
{
  switch (type)
  {
    case Symbol::Type::tINVALID:
      ostrm << "tINVALID";
      break;
    case Symbol::Type::tVOID:
      ostrm << "tVOID";
      break;
    case Symbol::Type::tINT:
      ostrm << "tINT";
      break;
    case Symbol::Type::tFLOAT:
      ostrm << "tFLOAT";
      break;
  }
  return ostrm;
}

std::string Symbol::toString() const
{
  if (type_ == tINVALID)
    return getName();

  std::ostringstream oss;
  oss << '<' << getName() << ':' << type_ << '>';
  return oss.str(); 
}


