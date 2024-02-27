# antlr_ref
Repo for code from the book The Definitive ANTLR4 Reference by Terence Parr

## code examples

All examples from the book have been implemented from scratch in Java and C++.
There is a README in each folder shpwing the build steps.

The java build requirements are the same as for the book files.

The C++ makefiles expect the following environment variables:

  STD_HEADERS
  ANTLR_HEADERS
  ANTLR_LIBS

Mine are currently set as follows:

export STD_HEADERS=/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include
export ANTLR_HEADERS="/Users/martinwaplington/Documents/Programming/antlr/source/antlr4-4.13.1/runtime/Cpp/run/usr/local/include/antlr4-runtime"
export ANTLR_LIBS="/Users/martinwaplington/Documents/Programming/antlr/source/antlr4-4.13.1/runtime/Cpp/run/usr/local/lib"


