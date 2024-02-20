import org.antlr.v4.runtime.*;
import java.util.*;
import javax.swing.*;
import java.awt.*;

public class DialogErrorListener extends BaseErrorListener
{
  @Override
  public void syntaxError(Recognizer<?, ?> recognizer,
                          Object offendingSymbol,
                          int line,
                          int charPositionInLine,
                          String msg,
                          RecognitionException e)
  {
    java.util.List<String> stack = ((Parser)recognizer).getRuleInvocationStack();
    Collections.reverse(stack);
    StringBuilder buf = new StringBuilder();
    buf.append("rule stack: " + stack + " ");
    buf.append("line " + line + ": " +
               charPositionInLine + " at " +
               offendingSymbol + ": " + msg);

    JDialog dialog = new JDialog();
    Container contentPane = dialog.getContentPane();
    contentPane.add(new JLabel(buf.toString()));
    contentPane.setBackground(Color.white);
    dialog.setTitle("Syntax error");
    dialog.pack();
    dialog.setLocationRelativeTo(null);
    dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    dialog.setVisible(true);
  }
}

