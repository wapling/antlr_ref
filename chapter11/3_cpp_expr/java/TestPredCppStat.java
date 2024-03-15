import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestPredCppStat
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      PredCppStatLexer lexer = new PredCppStatLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      PredCppStatParser parser = new PredCppStatParser(tokens);
      ParseTree tree = parser.stat();
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
