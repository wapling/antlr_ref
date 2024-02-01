import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestPropertyFile
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      PropertyFileLexer lexer = new PropertyFileLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      PropertyFileParser parser = new PropertyFileParser(tokens);
      ParseTree tree = parser.file();
      ParseTreeWalker walker = new ParseTreeWalker();
      PropertyFileLoader loader = new PropertyFileLoader();
      walker.walk(loader, tree);
      System.out.println(loader.props);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
