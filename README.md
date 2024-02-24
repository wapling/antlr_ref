# antlr_ref
Repo for code from the book The Definitive ANTLR4 Reference by Terence Parr

From ANTLR4 Reference pages 24-25:

grun is an alias:

  alias grun='java org.antlr.v4.gui.TestRig'

See (and source!) .antlr4131 in the parent directories of this file for antlr4 and clean etc.

Use jar tf to dump the classes in the antlr jar:

  jar tf /usr/local/lib/antlr-4.13.1-complete.jar > classes

Then use javap to dump the contents of a given class:

javap -classpath /usr/local/lib/antlr-4.13.1-complete.jar org/antlr/v4/codegen/model/Parser

