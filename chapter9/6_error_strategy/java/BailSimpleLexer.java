import org.antlr.v4.runtime.*;

public class BailSimpleLexer extends SimpleLexer
{
  public BailSimpleLexer(CharStream input)
  {
    super(input);
  }

  @Override
  public void recover(LexerNoViableAltException e)
  {
    //rethrow LexerNoViableAltException wrapped in a 
    //generic RuntimeException so that is not caught by rule functions.
    throw new RuntimeException(e);
  }
}

