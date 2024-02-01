import java.util.Map;
import org.antlr.v4.misc.OrderedHashMap;

class PropertyFileLoader extends PropertyFileBaseListener
{
  Map<String, String> props = new OrderedHashMap<String, String>();
  
	@Override
  public void exitProp(PropertyFileParser.PropContext ctx)
  {
    String id = ctx.ID().getText();
    String value = ctx.STRING().getText();
    props.put(id, value); 
  }
}

