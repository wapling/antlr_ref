import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.Token;

class AmbigErrorListener extends AmbigBaseListener
{
	@Override
  public void exitStat(AmbigParser.StatContext ctx)
  {
    System.out.println(ctx.ID().getText());
  }

	@Override
  public void exitExpr(AmbigParser.ExprContext ctx)
  {
    System.out.println(ctx.ID().getText());
  }

}

