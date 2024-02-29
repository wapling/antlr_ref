package tools;

import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;

class Calc
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      BufferedReader br = new BufferedReader(new InputStreamReader(is));
      String expr = br.readLine();
      int line = 1;
      ExprParser parser = new ExprParser(null);
      parser.setBuildParseTree(false);

      while (expr != null)
      {
        ANTLRInputStream input = new ANTLRInputStream(expr + '\n');
        ExprLexer lexer = new ExprLexer(input);
        lexer.setLine(line);
        lexer.setCharPositionInLine(0);
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        parser.setInputStream(tokens);
        parser.stat();
        expr = br.readLine();
        line++;
      }
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

