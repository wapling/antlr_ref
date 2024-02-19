import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.Token;

class SimpleErrorListener extends SimpleBaseListener
{
	@Override
  public void exitClassDef(SimpleParser.ClassDefContext ctx)
  {
    System.out.println("class: " + ctx.ID().getText());
  }

	@Override
  public void exitFieldDef(SimpleParser.FieldDefContext ctx)
  {
    System.out.println("var: " + ctx.ID().getText());
  }

	@Override
  public void exitMethodDef(SimpleParser.MethodDefContext ctx)
  {
    System.out.println("method: " + ctx.ID(0).getText());
  }

	@Override
  public void exitStatExpr(SimpleParser.StatExprContext ctx)
  {
    System.out.println("found expr: " + ctx.expr().getText());
  }

	@Override
  public void exitStatAssign(SimpleParser.StatAssignContext ctx)
  {
    System.out.println("found assign: " + ctx.expr().getText());
  }

}

