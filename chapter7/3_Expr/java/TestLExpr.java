import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestLExpr
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      LExprLexer lexer = new LExprLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      LExprParser parser = new LExprParser(tokens);
      ParseTree tree = parser.s();
      EvalVisitor visitor = new EvalVisitor();
      int result = visitor.visit(tree);
      System.out.println("Result = " + result);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
