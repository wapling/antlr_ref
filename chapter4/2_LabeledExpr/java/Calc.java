import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class Calc
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      LabeledExprLexer lexer = new LabeledExprLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      LabeledExprParser parser = new LabeledExprParser(tokens);
      ParseTree tree = parser.prog();
      EvalVisitor visitor = new EvalVisitor();
      visitor.visit(tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
