import java.util.Stack;
import org.antlr.v4.misc.OrderedHashMap;

class Evaluator extends LExprBaseListener
{
  Stack<Integer> stack = new Stack<Integer>();
 
	@Override
  public void exitAdd(LExprParser.AddContext ctx)
  {
    int rhs = stack.pop();
    int lhs = stack.pop();
    stack.push(lhs + rhs);
  }

	@Override
  public void exitMult(LExprParser.MultContext ctx)
  {
    int rhs = stack.pop();
    int lhs = stack.pop();
    stack.push(lhs * rhs);
  }

	@Override
  public void exitInt(LExprParser.IntContext ctx)
  {
    stack.push(Integer.valueOf(ctx.INT().getText()));
  }

}

