import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

public class JSON2XML
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      JSONLexer lexer = new JSONLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      JSONParser parser = new JSONParser(tokens);
      ParseTree tree = parser.json();
      ParseTreeWalker walker = new ParseTreeWalker();
      XMLEmitter_ST listener = new XMLEmitter_ST();
      walker.walk(listener, tree);
      System.out.println(decorateWithRoot(listener.xml.get(tree).render()));
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
  
  private static String decorateWithRoot(String xml_fragment)
  {
    return "<?xml version='1.0'?><root>" + xml_fragment + "</root>";
  } 
}
