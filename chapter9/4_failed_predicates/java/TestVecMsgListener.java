import org.antlr.v4.runtime.*;

class TestVecMsgListener extends VecMsgBaseListener
{
  int count;
  int max_count;

  public TestVecMsgListener(int max_count)
  {
    this.count = 0;
    this.max_count = max_count;
  }

	@Override
  public void exitFirst_int(VecMsgParser.First_intContext ctx)
  {
    count = 1;
  }

	@Override
  public void exitNext_int(VecMsgParser.Next_intContext ctx)
  {
    ++count;
    if (count > max_count)
    {
      Token token = ctx.INT().getSymbol();
      System.err.println("Line: " + Integer.toString(token.getLine()) + 
                         ":" + Integer.toString(token.getStartIndex()) +
                         " rule ints exceeded max " + Integer.toString(max_count));
    }
  }
}

