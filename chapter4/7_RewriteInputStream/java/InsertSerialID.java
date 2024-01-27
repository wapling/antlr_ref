import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class InsertSerialID
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      JavaLexer lexer = new JavaLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      JavaParser parser = new JavaParser(tokens);
      ParseTree tree = parser.compilationUnit();
      ParseTreeWalker walker = new ParseTreeWalker();
      InsertSerialIDListener listener = new InsertSerialIDListener(tokens);
      walker.walk(listener, tree);
      System.out.println(listener.rewriter.getText());
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
