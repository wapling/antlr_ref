import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class ExtractInterfaceTool
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
      ExtractInterfaceListener listener = new ExtractInterfaceListener(parser);
      walker.walk(listener, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
