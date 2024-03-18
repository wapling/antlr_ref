import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import java.util.*;

public class CommentShifter extends CymbolBaseListener
{
  BufferedTokenStream tokens;
  TokenStreamRewriter rewriter;

  public CommentShifter(BufferedTokenStream tokens)
  {
    this.tokens = tokens;
    rewriter = new TokenStreamRewriter(this.tokens);
  }

	@Override
  public void exitVarDecl(CymbolParser.VarDeclContext ctx)
  {
    Token semi = ctx.getStop();
    int i = semi.getTokenIndex();
    List<Token> cmtChannel = tokens.getHiddenTokensToRight(i, 2);
    if (cmtChannel != null)
    {
      Token cmt = cmtChannel.get(0);
      if (cmt != null)
      {
        String txt = cmt.getText().substring(2);
        String newCmt = "/*" + txt.trim() + "*/\n";
        rewriter.insertBefore(ctx.start, newCmt);
        rewriter.replace(cmt, "\n");
      }
    }
  }

}

