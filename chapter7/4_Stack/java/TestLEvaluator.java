import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestLEvaluator
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
      ParseTreeWalker walker = new ParseTreeWalker();
      Evaluator listener = new Evaluator();
      walker.walk(listener, tree);
      System.out.println("Stack result = " + listener.stack.pop());
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
