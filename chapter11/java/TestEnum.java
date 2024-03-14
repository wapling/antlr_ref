import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class TestEnum 
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
      EnumParser.java5 = isJava5(args);
      String filename = getFilename(args);

      InputStream is = (filename.length() > 0) ? new FileInputStream(filename) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      EnumLexer lexer = new EnumLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      EnumParser parser = new EnumParser(tokens);
      ParseTree tree = parser.prog();
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}
