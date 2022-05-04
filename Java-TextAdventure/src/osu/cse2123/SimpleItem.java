package osu.cse2123;

/**
 * 
 * @author Jake Kennedy
 * @version 4/25/2022
 */

public class SimpleItem implements Item {

	private String name;
	private String desc;
	
	@Override
	public void setName(String name) {
		this.name=name;

	}

	@Override
	public String getName() {
		return this.name;
	}

	@Override
	public void setDesc(String desc) {
		this.desc=desc;

	}

	@Override
	public String getDesc() {
		return this.desc;
	}
	
	@Override
	public String toString() {
		return this.name+", "+this.desc;
	}

}
