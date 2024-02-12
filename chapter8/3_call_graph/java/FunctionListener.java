import java.util.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.misc.MultiMap;
import org.antlr.v4.runtime.misc.OrderedHashSet;

class FunctionListener extends CymbolBaseListener
{
  String currentFunctionName = null;
  Set<String> nodes = new OrderedHashSet<String>();
  MultiMap<String, String> edges = new MultiMap<String, String>();

	@Override
  public void enterFunctionDecl(CymbolParser.FunctionDeclContext ctx)
  {
    currentFunctionName = ctx.ID().getText();
    nodes.add(currentFunctionName);
  }

	@Override
  public void exitCall(CymbolParser.CallContext ctx)
  {
    String callName = ctx.ID().getText();
    edges.map(currentFunctionName, callName);
  }

  private String getDotBoilerplatePrefix()
  {
    return
      """
digraph G
{
  ranksep = .25;
  edge [arrowsize = .5]
  node [shape = circle, fontname = "ArialNarrow",
        fontsize = 12, fixedsize = true, height = .45];
""";
  }

  private String getDotBoilerplatePostfix()
  {
    return "}\n";
  }

  public String toDot()
  {
    StringBuilder buf = new StringBuilder();
    buf.append(getDotBoilerplatePrefix());
    for (String node : nodes)
    {
      buf.append(node);
      buf.append("; ");
    }
    buf.append("\n");
    for (String source : edges.keySet())
    {
      for (String target : edges.get(source))
      {
        buf.append("   ");
        buf.append(source);
        buf.append(" -> ");
        buf.append(target);
        buf.append(";\n");
      }
    }
    buf.append(getDotBoilerplatePostfix());
    return buf.toString();
  }
}

