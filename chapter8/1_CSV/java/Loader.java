import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

class Loader extends CSVBaseListener
{
  public static final String EMPTY = "";

  List<Map<String, String>> rows = new ArrayList<Map<String, String>>();

  List<String> header;
  List<String> currentRowFieldValues; 
	
	@Override
  public void exitHdr(CSVParser.HdrContext ctx)
  {
    header = new ArrayList<String>();
    header.addAll(currentRowFieldValues);
  }

	@Override
  public void enterRow(CSVParser.RowContext ctx)
  {
    currentRowFieldValues = new ArrayList<String>();
  }

	@Override
  public void exitRow(CSVParser.RowContext ctx)
  {
    if (ctx.getParent().getRuleIndex() == CSVParser.RULE_hdr)
      return;

    Map<String, String> new_row = new LinkedHashMap<String, String>();
    for (int i=0, n=currentRowFieldValues.size(); i < n; i++)
      new_row.put(header.get(i), currentRowFieldValues.get(i));

    rows.add(new_row);
  }

	@Override
  public void exitText(CSVParser.TextContext ctx)
  {
    currentRowFieldValues.add(ctx.TEXT().getText());
  }

	@Override
  public void exitString(CSVParser.StringContext ctx)
  {
    currentRowFieldValues.add(ctx.STRING().getText());
  }

  @Override
  public void exitEmpty(CSVParser.EmptyContext ctx)
  {
    currentRowFieldValues.add(EMPTY);
  }

}
