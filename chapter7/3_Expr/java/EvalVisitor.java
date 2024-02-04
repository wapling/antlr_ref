

class EvalVisitor extends LExprBaseVisitor<Integer>
{
	@Override
  public Integer visitAdd(LExprParser.AddContext ctx)
  {
    return visit(ctx.e(0)) + visit(ctx.e(1));
  }

	@Override
  public Integer visitMult(LExprParser.MultContext ctx)
  {
    return visit(ctx.e(0)) * visit(ctx.e(1));
  }

	@Override
  public Integer visitInt(LExprParser.IntContext ctx)
  {
    return Integer.valueOf(ctx.INT().getText());
  }
}

