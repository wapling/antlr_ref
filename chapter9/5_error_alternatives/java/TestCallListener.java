import org.antlr.v4.runtime.*;

class TestCallListener extends CallBaseListener
{
  CallParser parser;

  public TestCallListener(CallParser parser)
  {
    this.parser = parser;
  }

	@Override
  public void exitExtra_paren(CallParser.Extra_parenContext ctx)
  {
    parser.notifyErrorListeners("Too many parentheses");
  }

	@Override
  public void exitMissing_paren(CallParser.Missing_parenContext ctx)
  {
    parser.notifyErrorListeners("Missing closing parenthesis");
  }
}

