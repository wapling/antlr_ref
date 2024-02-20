import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

class TestE_Listener2
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      SimpleLexer lexer = new SimpleLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      SimpleParser parser = new SimpleParser(tokens);
      parser.removeErrorListeners();
      parser.addErrorListener(new UnderlineErrorListener());
      ParseTree tree = parser.prog();
      ParseTreeWalker walker = new ParseTreeWalker();
      SimpleErrorListener listener = new SimpleErrorListener();
      walker.walk(listener, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

