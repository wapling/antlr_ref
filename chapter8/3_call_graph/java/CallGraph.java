import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

class CallGraph
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      CymbolLexer lexer = new CymbolLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      CymbolParser parser = new CymbolParser(tokens);
      ParseTree tree = parser.file();
      ParseTreeWalker walker = new ParseTreeWalker();
      FunctionListener listener = new FunctionListener();
      walker.walk(listener, tree);
      System.out.println(listener.toDot());
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

