import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

class CheckSymbol
{
  public static Symbol.Type getType(int tokenType)
  {
    switch ( tokenType )
    {
      case CymbolParser.K_VOID :  return Symbol.Type.tVOID;
      case CymbolParser.K_INT :   return Symbol.Type.tINT;
      case CymbolParser.K_FLOAT : return Symbol.Type.tFLOAT;
    }
    return Symbol.Type.tINVALID;
  }

  public static void error(Token t, String msg)
  {
    System.err.printf("line %d:%d %s\n",
                      t.getLine(),
                      t.getCharPositionInLine(),
                      msg);
  }

  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      CymbolLexer lexer = new CymbolLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      CymbolParser parser = new CymbolParser(tokens);
      ParseTree tree = parser.file();
      ParseTreeWalker walker = new ParseTreeWalker();
      DefPhase def = new DefPhase();
      walker.walk(def, tree);
      RefPhase ref = new RefPhase(def.globals, def.scopes);
      walker.walk(ref, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

