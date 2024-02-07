import org.antlr.v4.runtime.tree.*;
import org.stringtemplate.v4.ST;
import org.stringtemplate.v4.STGroup;
import org.stringtemplate.v4.STGroupFile;

class XMLEmitter_ST extends JSONBaseListener
{
  ParseTreeProperty<ST> xml = new ParseTreeProperty<ST>();
  STGroup templates = new STGroupFile("XML.stg");

	@Override
  public void exitAtom(JSONParser.AtomContext ctx)
  {
    ST st = templates.getInstanceOf("value");
    st.add("x", ctx.getText());
    xml.put(ctx, st);
  }

	@Override
  public void exitString(JSONParser.StringContext ctx)
  {
    ST st = templates.getInstanceOf("value");
    st.add("x", stripQuotes(ctx.getText()));
    xml.put(ctx, st);
  }

	@Override
  public void exitObjectValue(JSONParser.ObjectValueContext ctx)
  {
    xml.put(ctx, xml.get(ctx.object()));
  }

	@Override
  public void exitPair(JSONParser.PairContext ctx)
  {
    String name = stripQuotes(ctx.STRING().getText());
    JSONParser.ValueContext vctx = ctx.value();
    ST st = templates.getInstanceOf("tag");
    st.add("name", name);
    st.add("content", xml.get(vctx));
    xml.put(ctx, st);
  }

	@Override
  public void exitAnObject(JSONParser.AnObjectContext ctx)
  {
    ST st = templates.getInstanceOf("object");
    for (JSONParser.PairContext pctx : ctx.pair())
      st.add("fields", xml.get(pctx));
    xml.put(ctx, st);
  }

	@Override
  public void exitEmptyObject(JSONParser.EmptyObjectContext ctx)
  {
    ST st = templates.getInstanceOf("empty");
    xml.put(ctx, st);
  }

	@Override
  public void exitArrayOfValues(JSONParser.ArrayOfValuesContext ctx)
  {
    ST st = templates.getInstanceOf("array");
    for (JSONParser.ValueContext vctx : ctx.value())
      st.add("values", xml.get(vctx));
    xml.put(ctx, st);
  }

	@Override
  public void exitEmptyArray(JSONParser.EmptyArrayContext ctx)
  {
    ST st = templates.getInstanceOf("empty");
    xml.put(ctx, st);
  }

	@Override
  public void exitJson(JSONParser.JsonContext ctx)
  {
    xml.put(ctx, (xml.get(ctx.getChild(0))));
  }

  public static String stripQuotes(String s)
  {
    if (s == null || s.charAt(0) != '"')
      return s;
    return s.substring(1, s.length() - 1);
  }
}
