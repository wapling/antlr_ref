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
      VecMsgLexer lexer = new VecMsgLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      VecMsgParser parser = new VecMsgParser(tokens);
      ParseTree tree = parser.vec4();
      ParseTreeWalker walker = new ParseTreeWalker();
      TestVecMsgListener listener = new TestVecMsgListener(4);
      walker.walk(listener, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

