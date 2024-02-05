import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class LoadCSV
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      CSVLexer lexer = new CSVLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      CSVParser parser = new CSVParser(tokens);
      ParseTree tree = parser.file();
      ParseTreeWalker walker = new ParseTreeWalker();
      Loader loader = new Loader();
      walker.walk(loader, tree);
      System.out.println(loader.rows);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
