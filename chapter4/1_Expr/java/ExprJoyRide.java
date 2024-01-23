import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class ExprJoyRide
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      ExprLexer lexer = new ExprLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      ExprParser parser = new ExprParser(tokens);
      ParseTree tree = parser.prog();
      System.out.println(tree.toStringTree(parser));
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
