# antlr_ref
Repo for code from the book The Definitive ANTLR4 Reference by Terence Parr

From ANTLR4 Reference pages 24-25:

grun is an alias:

  alias grun='java org.antlr.v4.gui.TestRig'

See (and source!) .antlr4131 in the parent directories of this file for antlr4 and clean etc.

In tmp/test_cpp is a C++ example created by running:

  antlr4 -Dlanguage=Cpp Hello.g4 

In tmp/test_java is a Java example which matches the book, created by running:

  antlr4 Hello.g4
  javac *.java

To test it run:
  grun Hello r -tokens
  grun Hello r -tree
  grun Hello r -gui

Then enter: 
  hello parrt

In tmp/test_python is a Python example created by running:

  antlr4 -Dlanguage=Python3 Hello.g4 

Finish with Ctrl-D for the following output:

[@0,0:4='hello',<'hello'>,1:0]
[@1,6:10='parrt',<ID>,1:6]
[@2,12:11='<EOF>',<EOF>,2:0]


When running grun with -gui be prepared to wait for GUI to both start and finish.

TODO 
  - write a harness for the java parser
  - write a harness for the C++ parser
  - create a python parser and write a harness for that
  - Go?

