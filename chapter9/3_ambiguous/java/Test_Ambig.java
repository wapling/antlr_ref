import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.atn.*;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStream;

class Test_Ambig
{
  public static void main(String[] args)
  {
    try
    {
      InputStream is = (args.length > 0) ? new FileInputStream(args[0]) : System.in;
      ANTLRInputStream input = new ANTLRInputStream(is);
      AmbigLexer lexer = new AmbigLexer(input);
      CommonTokenStream tokens = new CommonTokenStream(lexer);
      AmbigParser parser = new AmbigParser(tokens);

      //parser.removeErrorListeners();
      parser.addErrorListener(new DiagnosticErrorListener());
      parser.getInterpreter().setPredictionMode(PredictionMode.LL_EXACT_AMBIG_DETECTION);

      ParseTree tree = parser.stat();
      ParseTreeWalker walker = new ParseTreeWalker();
      AmbigErrorListener listener = new AmbigErrorListener();
      walker.walk(listener, tree);
    }
    catch (IOException ex)
    {
      System.err.println("An error occurred: " + ex);
    }
  }
}

