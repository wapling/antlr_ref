import org.antlr.v4.runtime.*;

public class BailErrorStrategy extends DefaultErrorStrategy
{
  @Override
  public void recover(Parser recognizer, RecognitionException e)
  {
    //rethrow RecognitionException wrapped in a generic RuntimeException
    //so that is not caught by rule functions.
    throw new RuntimeException(e);
  }

  @Override
  public Token recoverInline(Parser recognizer) throws RecognitionException
  {
    //don't attempt to recover inline
    throw new RuntimeException(new InputMismatchException(recognizer));
  }

  @Override
  public void sync(Parser recognizer)
  {
    //don't attempt to recover, we are bailing!
  }
}

