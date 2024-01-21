import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;

public class Test
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
      System.out.println(tree.toStringTree(parser));
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
