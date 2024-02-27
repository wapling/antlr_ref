import org.antlr.v4.runtime.*;

public class MyErrorStrategy extends DefaultErrorStrategy
{
  @Override
  protected void reportNoViableAlternative(Parser parser, NoViableAltException e)
    throws RecognitionException
  {
    String msg = "CUSTOM MESSAGE: Can't choose between alternatives";
    parser.notifyErrorListeners(e.getOffendingToken(), msg, e);
  }
}

