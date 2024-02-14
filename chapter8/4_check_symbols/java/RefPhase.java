import org.antlr.v4.runtime.tree.*;

class RefPhase extends CymbolBaseListener
{
  ParseTreeProperty<Scope> scopes;
  GlobalScope globals;
  Scope currentScope;

  public RefPhase(GlobalScope globals, ParseTreeProperty<Scope> scopes)
  {
    this.scopes = scopes;
    this.globals = globals;
  }

	@Override
  public void enterFile(CymbolParser.FileContext ctx)
  {
    currentScope = globals;
  }

	@Override
  public void enterFunctionDecl(CymbolParser.FunctionDeclContext ctx)
  {
    currentScope = scopes.get(ctx);
  }

	@Override
  public void exitFunctionDecl(CymbolParser.FunctionDeclContext ctx)
  {
    currentScope = currentScope.getEnclosingScope();
  }

	@Override
  public void enterBlock(CymbolParser.BlockContext ctx)
  {
    currentScope = scopes.get(ctx);
  }

	@Override
  public void exitBlock(CymbolParser.BlockContext ctx)
  {
    currentScope = currentScope.getEnclosingScope();
  }

	@Override
  public void exitVar(CymbolParser.VarContext ctx)
  {
    String name = ctx.ID().getSymbol().getText();
    Symbol variable = currentScope.resolve(name);
    if (variable == null)
    {
      CheckSymbol.error(ctx.ID().getSymbol(), "No such variable: " + name);
    }
    else if (variable instanceof FunctionSymbol)
    {
      CheckSymbol.error(ctx.ID().getSymbol(), name + " is not a variable.");
    }
  }

	@Override
  public void exitCall(CymbolParser.CallContext ctx)
  {
    String call = ctx.ID().getSymbol().getText();
    Symbol function = currentScope.resolve(call);
    if (function == null)
    {
      CheckSymbol.error(ctx.ID().getSymbol(), "No such function: " + call);
    }
    else if (function instanceof VariableSymbol)
    {
      CheckSymbol.error(ctx.ID().getSymbol(), call + " is not a function.");
    }
  }
}

