import org.antlr.v4.runtime.tree.*;

class EvaluatorWithProps extends LExprBaseListener
{
  ParseTreeProperty<Integer> values = new ParseTreeProperty<Integer>();

  public void setValue(ParseTree node, int value)
  {
    values.put(node, value);
  }

  public int getValue(ParseTree node)
  {
    return values.get(node);
  }

	@Override
  public void exitAdd(LExprParser.AddContext ctx)
  {
    int lhs = getValue(ctx.e(0));
    int rhs = getValue(ctx.e(1));
    setValue(ctx, lhs + rhs);
  }

	@Override
  public void exitMult(LExprParser.MultContext ctx)
  {
    int lhs = getValue(ctx.e(0));
    int rhs = getValue(ctx.e(1));
    setValue(ctx, lhs * rhs);
  }

	@Override
  public void exitInt(LExprParser.IntContext ctx)
  {
    setValue(ctx, Integer.valueOf(ctx.INT().getText()));
  }

	@Override
  public void exitS(LExprParser.SContext ctx)
  {
    setValue(ctx, getValue(ctx.e()));
  }
}

