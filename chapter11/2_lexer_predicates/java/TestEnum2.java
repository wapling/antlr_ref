import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestEnum2 
{
  public static boolean isJava5(String[] args)
  {
    for (String arg : args)
      if (arg.equals("-java5"))
        return true;
    return false;
  }

  public static String getFilename(String[] args)
  {
    for (String arg : args)
      if (!arg.equals("-java5"))
        return arg;
    return "";
  }

  public static void main(String[] args)
  {
    try
    {
      Enum2Lexer.java5 = isJava5(args);
      String filename = getFilename(args);

      InputStream is = (filename.length() > 0) ? new FileInputStream(filename) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      Enum2Lexer lexer = new Enum2Lexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      Enum2Parser parser = new Enum2Parser(tokens);
      ParseTree tree = parser.prog();
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
