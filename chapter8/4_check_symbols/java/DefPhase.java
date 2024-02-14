import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.Token;

class DefPhase extends CymbolBaseListener
{
  ParseTreeProperty<Scope> scopes = new ParseTreeProperty<Scope>();
  GlobalScope globals;
  Scope currentScope;


	@Override
  public void enterFile(CymbolParser.FileContext ctx)
  {
    globals = new GlobalScope(null);
    currentScope = globals;
  }

	@Override
  public void exitFile(CymbolParser.FileContext ctx)
  {
    System.out.println(globals);
  }

	@Override
  public void enterFunctionDecl(CymbolParser.FunctionDeclContext ctx)
  {
    String name = ctx.ID().getText();
    int typeTokenType = ctx.type().start.getType();
    Symbol.Type type = CheckSymbol.getType(typeTokenType);

    FunctionSymbol function = new FunctionSymbol(name, type, currentScope);
    currentScope.define(function);
    scopes.put(ctx, function);
    currentScope = function;
  }

	@Override
  public void exitFunctionDecl(CymbolParser.FunctionDeclContext ctx)
  {
    System.out.println(currentScope);
    currentScope = currentScope.getEnclosingScope();
  }

	@Override
  public void enterBlock(CymbolParser.BlockContext ctx)
  {
    currentScope = new LocalScope(currentScope);
    scopes.put(ctx, currentScope);
  }

	@Override
  public void exitBlock(CymbolParser.BlockContext ctx)
  {
    System.out.println(currentScope);
    currentScope = currentScope.getEnclosingScope();
  }

	@Override
  public void exitFormalParameter(CymbolParser.FormalParameterContext ctx)
  {
    defineVar(ctx.type(), ctx.ID().getSymbol());
  }

	@Override
	public void exitVarDecl(CymbolParser.VarDeclContext ctx)
  {
    defineVar(ctx.type(), ctx.ID().getSymbol());
  }

  void defineVar(CymbolParser.TypeContext typeCtx, Token nameToken)
  {
    int typeTokenType = typeCtx.start.getType();
    Symbol.Type type = CheckSymbol.getType(typeTokenType);
    VariableSymbol varSym = new VariableSymbol(nameToken.getText(), type);
    currentScope.define(varSym);
  }
}

