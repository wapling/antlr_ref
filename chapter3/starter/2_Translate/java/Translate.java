import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;

public class Translate
{
  public static void main(String[] args)
  {
    try
    {
      ANTLRInputStream input = new ANTLRInputStream(System.in);
      ArrayInitLexer lexer = new ArrayInitLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      ArrayInitParser parser = new ArrayInitParser(tokens);
      ParseTree tree = parser.init();
      ParseTreeWalker walker = new ParseTreeWalker();
      walker.walk(new ShortToUnicodeString(), tree);
      System.out.println();
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
