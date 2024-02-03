import java.util.Map;
import org.antlr.v4.misc.OrderedHashMap;

class PropertyFileLoader extends PropertyFileBaseVisitor<Void>
{
  Map<String, String> props = new OrderedHashMap<String, String>();
  
	@Override
  public Void visitProp(PropertyFileParser.PropContext ctx)
  {
    String id = ctx.ID().getText();
    String value = ctx.STRING().getText();
    props.put(id, value);
    return null; 
  }
}

