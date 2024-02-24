import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

class Test
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      CallLexer lexer = new CallLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      CallParser parser = new CallParser(tokens);
      ParseTree tree = parser.stat();
      ParseTreeWalker walker = new ParseTreeWalker();
      TestCallListener listener = new TestCallListener(parser);
      walker.walk(listener, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

