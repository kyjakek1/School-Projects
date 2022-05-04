package osu.cse2123;
/**
 * 
 * @author Jake Kennedy
 * @version 4/25/2022
 */
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

public class SimpleRoom implements Room {

	private String name;
	private List<String> desc;
	private Map<String,String> exits;
	private Map<String,Item> items;
	
	public SimpleRoom() {
		this.name="";
		this.desc=new LinkedList<>();
		this.exits=new HashMap<>();
		this.items=new HashMap<>();
	}
	
	@Override
	public void setName(String name) {
		this.name=name;
	}

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public void setDesc(List<String> desc) {
		this.desc=desc;

	}

	@Override
	public String getDesc() {
		StringBuilder desc=new StringBuilder();
		for(int i=0;i<this.desc.size();i++) {
			desc.append(this.desc.get(i));
			desc.append(System.lineSeparator());
		}
		return desc.toString();
	}

	@Override
	public void setExit(String direction, String dest) {
		this.exits.put(direction, dest);
	}

	@Override
	public boolean hasExit(String direction) {
		return this.exits.containsKey(direction);
	}

	@Override
	public String getExit(String direction) {
		return this.exits.get(direction);
	}

	@Override
	public void addItem(Item it) {
		this.items.put(it.getName(), it);

	}

	@Override
	public boolean hasItem(String name) {
		return this.items.containsKey(name);
	}

	@Override
	public Item removeItem(String name) {
		return this.items.remove(name);
	}
	
	@Override
	public String toString() {
		return this.name+", "+this.getDesc()+this.exits.toString()+this.items.toString();
	}

}
