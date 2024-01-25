import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.misc.Interval;

class ExtractInterfaceListener extends JavaBaseListener
{
  JavaParser parser;

  public ExtractInterfaceListener(JavaParser parser)
  {
    this.parser = parser;
  }

	@Override
  public void enterImportDeclaration(JavaParser.ImportDeclarationContext ctx)
  {
    TokenStream tokens = parser.getTokenStream();
    System.out.println(tokens.getText(ctx));
  }

	@Override
  public void enterClassDeclaration(JavaParser.ClassDeclarationContext ctx)
  {
    System.out.println("Interface I" + ctx.Identifier() + "\n{");
  }

	@Override
  public void exitClassDeclaration(JavaParser.ClassDeclarationContext ctx)
  {
    System.out.println("\n}\n");
  }

	@Override
  public void enterMethodDeclaration(JavaParser.MethodDeclarationContext ctx)
  {
    TokenStream tokens = parser.getTokenStream();
    String type = "void";
    if (ctx.type() != null)
    {
      type = tokens.getText(ctx.type());
    }
    String args = tokens.getText(ctx.formalParameters());
    System.out.println("\t" + type + " " + ctx.Identifier() + args + ";");
  }

}

