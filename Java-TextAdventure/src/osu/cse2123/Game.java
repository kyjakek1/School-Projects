package osu.cse2123;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;

/**
 * Add your header here
 * @author Jake Kennedy
 * @version 4/25/2022 
 *
 */

public class Game {

	/**
	 * returns a single room object from section of input file
	 * @param file input file with information about rooms
	 * @return room object with name, exits, and description variables filled out
	 */
	public static Room loadSingleRoom(Scanner file) {
		/*declare new room object and list to store lines from file*/
		Room room=new SimpleRoom();
		List<String> temp=new LinkedList<>();
		/*loop until next section is found, storing each line in list*/
		String loop=file.nextLine();
		while(!loop.equals("---")) {
			temp.add(loop);
			loop=file.nextLine();
		}
		/*set name to first element in list*/
		room.setName(temp.remove(0));
		/*create string array from splitting direction and exits*/
		String[] exits=temp.remove(0).split(",");
		/*loop for length of array, checking which direction and then setting exit in 
		 * room object to corresponding direction
		 */
		for(int i=0;i<exits.length;i++) {
			if(exits[i].charAt(0)=='N') {
				room.setExit("North", exits[i].substring(2));
			}else if(exits[i].charAt(0)=='E') {
				room.setExit("East", exits[i].substring(2));
			}else if(exits[i].charAt(0)=='S') {
				room.setExit("South", exits[i].substring(2));
			}else if(exits[i].charAt(0)=='W') {
				room.setExit("West", exits[i].substring(2));
			}else if(exits[i].charAt(0)=='U') {
				room.setExit("Up", exits[i].substring(2));
			}else if(exits[i].charAt(0)=='D') {
				room.setExit("Down", exits[i].substring(2));
			}
		}
		/*set description to the remaining list*/
		room.setDesc(temp);
		return room;
	}
	
	/**
	 * loads all of the rooms from input file "rooms.txt" into a map
	 * @return map of the rooms with room names as keys and corresponding room objects as values
	 * @throws FileNotFoundException
	 */
	public static Map<String,Room> loadRooms() throws FileNotFoundException {
		/*create new scanner for input file, and declare new map to store rooms*/
		Scanner roomFile=new Scanner(new File("rooms.txt"));
		Map<String,Room> rooms=new HashMap<>();
		
		/*loop until end of file*/
		while(roomFile.hasNextLine()) {
			/*load rooms and add them to map*/
			Room temp=loadSingleRoom(roomFile);
			rooms.put(temp.getName(), temp);
		}
		roomFile.close();
		return rooms;
	}
	
	/**
	 * Adds an item to the specified room
	 * @param rooms map of room names to room objects
	 * @param item item to be added
	 * @param location name of the room the object is to be added
	 */
	public static void loadItemIntoRoom(Map<String,Room> rooms, Item item,String location) {
		rooms.get(location).addItem(item);
	}
	
	/**
	 * creates a single item object from section of input file,
	 * also loads it into appropriate room object
	 * @param file input file containing information about items
	 * @param rooms map of room names to room objects
	 * @return item object with name and desc variables filled
	 */
	public static Item loadSingleItem(Scanner file,Map<String,Room> rooms) {
		/*create new item and list objects*/
		Item item=new SimpleItem();
		List<String> temp=new LinkedList<>();
		/*Scan until next item section, loading each line into list*/
		String loop=file.nextLine();
		while(!loop.equals("---")) {
			temp.add(loop);
			loop=file.nextLine();
		}
		/*set name to first element in list*/
		item.setName(temp.remove(0).toLowerCase());
		/*set desc to second item in list*/
		item.setDesc(temp.remove(0));
		loadItemIntoRoom(rooms,item,temp.remove(0));
		
		return item;
	}
	
	/**
	 * loads all of the items from the input file "items.txt" into a list
	 * @param rooms map of room names to room objects
	 * @return list of item objects containing all items in input file
	 * @throws FileNotFoundException
	 */
	public static List<Item> loadItems(Map<String,Room> rooms) throws FileNotFoundException{
		/*declare new scanner for item input file and new list to store items*/
		Scanner itemFile=new Scanner(new File("items.txt"));
		List<Item> items=new LinkedList<>();
		/*loop until end of file, adding items into list*/
		while(itemFile.hasNextLine()) {
			items.add(loadSingleItem(itemFile,rooms));
		}
		
		itemFile.close();
		return items;
	}
	
	/**
	 * Internal logic for the game loop, takes input from user and deciphers it, returning
	 * whether it was an error or appropriate request
	 * @param input user action input from keyboard
	 * @param rooms map of room names to room objects
	 * @param items list of items
	 * @param currentRoom users current location in the game
	 * @param inventory map of item names to item objects that make up the users inventory
	 * @return string specifying result of the user input, either an error, inventory, or a room
	 */
	public static String processRequest(String input,Map<String,Room> rooms,List<Item> items,String currentRoom,Map<String,Item> inventory) {
		String result=currentRoom;
		/*branch depending on request, if go, get, drop, inventory, or something else*/
		if(input.toLowerCase().startsWith("go ")) {
			/*get rest of request, check if it is an adequate direction,
			 * if so check if current room has that exit and move to that room if so,
			 * if not return an error
			 */
			String sub=input.substring(3);
			if(sub.equalsIgnoreCase("north")) {
				if(rooms.get(currentRoom).hasExit("North")) {
					result=rooms.get(currentRoom).getExit("North");
				}else {
					result="noExitError";
				}
			}else if(sub.equalsIgnoreCase("east")) {
				if(rooms.get(currentRoom).hasExit("East")) {
					result=rooms.get(currentRoom).getExit("East");
				}else {
					result="noExitError";
				}
			}else if(sub.equalsIgnoreCase("south")) {
				if(rooms.get(currentRoom).hasExit("South")) {
					result=rooms.get(currentRoom).getExit("South");
				}else {
					result="noExitError";
				}
			}else if(sub.equalsIgnoreCase("west")) {
				if(rooms.get(currentRoom).hasExit("West")) {
					result=rooms.get(currentRoom).getExit("West");
				}else {
					result="noExitError";
				}
			}else if(sub.equalsIgnoreCase("up")) {
				if(rooms.get(currentRoom).hasExit("Up")) {
					result=rooms.get(currentRoom).getExit("Up");
				}else {
					result="noExitError";
				}
			}else if(sub.equalsIgnoreCase("down")) {
				if(rooms.get(currentRoom).hasExit("Down")) {
					result=rooms.get(currentRoom).getExit("Down");
				}else {
					result="noExitError";
				}
			}else {
				result="directionError";
			}
		}else if(input.toLowerCase().startsWith("get ")) {
			/*get rest of request, check if current room has that item
			 * if so put the item in inventory and remove from room
			 * if not return error
			 */
			String sub=input.substring(4);
			if(rooms.get(currentRoom).hasItem(sub)) {
				Item temp=rooms.get(currentRoom).removeItem(sub);
				inventory.put(sub, temp);
				System.out.println("You pick up "+temp.getDesc()+".");
				System.out.println();
			}else {
				result="notInRoomError";
			}
		}else if(input.toLowerCase().startsWith("drop ")) {
			/*get rest of request, check if request is in inventory,
			 * if so remove from inventory and place in current room
			 * if not return error
			 */
			String sub=input.substring(5);
			if(inventory.containsKey(sub)) {
				Item temp=inventory.remove(sub);
				rooms.get(currentRoom).addItem(temp);
				System.out.println("You drop "+temp.getDesc()+".");
				System.out.println();
			}else {
				result="notInIError";
			}
		}else if(input.equalsIgnoreCase("inventory")) {
			/*if request was inventory return inventory keyword*/
			result="inventory";
		}else {
			/*if not an applicable request return error*/
			result="error";
		}
		
		return result;
	}
	
	/**
	 * prints out various error statements depending on processed request
	 * @param result the result returned by processRequest function
	 * @param input the users original input
	 * @return true if there are errors, false if there are no errors
	 */
	public static boolean processErrors(String result,String input) {
		boolean hasErrors=false;
		/*check for each type of error, printing appropriate error messages and returning true if ss,
		 * if no error message matches, return false
		 */
		if(result.equals("error")) {
			System.out.println("Error: Could not recognize this command, please try again");
			hasErrors=true;
		}else if(result.equals("noExitError")) {
			System.out.println("Error: This room does not have an exit in this direction, please try again");
			hasErrors=true;
		}else if(result.equals("directionError")) {
			System.out.println("Error: This direction is not recognized, please try again");
			hasErrors=true;
		}else if(result.equals("notInRoomError")) {
			System.out.println("There is no "+input.substring(4)+" here.");
			System.out.println();
			hasErrors=true;
		}else if(result.equals("notInIError")) {
			System.out.println("Error: This item could not be found in your inventory, please try again");
			hasErrors=true;
		}
		
		
		return hasErrors;
	}
	
	/**
	 * prints out the inventory for user to see
	 * @param inventory map of item names to item objects making up the users inventory
	 */
	public static void displayInventory(Map<String,Item> inventory) {
		System.out.println("You are currently carrying:");
		/*if inventory isnt empty, print out every item in inventory,
		 * if is empty, print out "nothing"
		 */
		if(!inventory.isEmpty()) {
			Set<String> keys=inventory.keySet();
			for(String s:keys) {
				System.out.println("   "+inventory.get(s).getDesc());
			}
		}else {
			System.out.println("   nothing");
		}
		System.out.println();
	}
	
	/**
	 * Main driver of the game, loops until user decides to quit, allows navigation, and object interaction
	 * prints information about room and surroundings for user to interact with
	 * @param rooms map of room names to room objects
	 * @param items list of items 
	 * @param keyboard System.in input stream
	 */
	public static void mainGameLoop(Map<String,Room> rooms,List<Item> items,Scanner keyboard) {
		/*initialize input as startkey (used to skip request processing) and current room as entry room*/
		String input="STARTKEY";
		String currentRoom="Entry Room";
		Map<String,Item> inventory=new HashMap<>();
		boolean errors=false;
		/*loop until user decides to quit*/
		while(!input.equalsIgnoreCase("quit")) {
			/*if input doesnt equal startkey, user request has been entered*/
			if(!input.equals("STARTKEY")) {
				/*process user input, and process any errors returned*/
				String result=processRequest(input,rooms,items,currentRoom,inventory);
				errors=processErrors(result,input);
				/*if request returned inventory, display it,
				 * if not and there were no errors, set current room 
				 * to what processRequest returned
				 */
				if(result.equals("inventory")) {
					displayInventory(inventory);
				}else if(!errors) {
					currentRoom=result;
				}
			}
				/*after processing input, or just starting game
				 * declare new room as currentRoom
				 */
				Room entry=rooms.get(currentRoom);
				
				/*print name, description, and exits to screen for users to see*/
				System.out.println(entry.getName());
				System.out.print(entry.getDesc());
				System.out.print("There are exits in the following directions: ");
				/*internal if statements are for comma formatting only and are trivial*/
				boolean format=false;
				if(entry.hasExit("East")){
					if(format) System.out.print(", ");
					System.out.print("east");
					format=true;
				}
				if(entry.hasExit("North")) {
					if(format) System.out.print(", ");
					System.out.print("north");
					format=true;
				}
				if(entry.hasExit("South")){
					if(format) System.out.print(", ");
					System.out.print("south");
					format=true;
				}
				if(entry.hasExit("West")){
					if(format) System.out.print(", ");
					System.out.print("west");
					format=true;
				}
				if(entry.hasExit("Up")){
					if(format) System.out.print(", ");
					System.out.print("up");
					format=true;
				}
				if(entry.hasExit("Down")){
					if(format) System.out.print(", ");
					System.out.print("down");
				}
				System.out.println();

				/*loop over amount of items,
				 * if room has item, print it to screen
				 */
				for(int i=0;i<items.size();i++) {
					if(entry.hasItem(items.get(i).getName())){
						System.out.println("There is "+items.get(i).getDesc()+" here.");				
					}
				}
			
			/*get user input, if they type quit, double check they meant it*/
			System.out.println();
			System.out.print("> ");
			
			input=keyboard.nextLine();
			
			if(input.equalsIgnoreCase("quit")) {
				System.out.println("Are you sure you want to quit?");
				System.out.print("> ");
				String sure=keyboard.nextLine();
				if(!sure.equalsIgnoreCase("y")&&!sure.equalsIgnoreCase("yes")) {
					input="STARTKEY";
				}
			}
		}
	}
	
	public static void main(String[] args) throws FileNotFoundException{
		/*Declare new input stream from keyboard*/
		Scanner keyboard=new Scanner(System.in);
		/*Create rooms map and items list from appropriate functions*/
		Map<String,Room> rooms=loadRooms();
		List<Item> items=loadItems(rooms);
		/*start main game loop*/
		mainGameLoop(rooms,items,keyboard);
		
		
		/*close scanner*/
		keyboard.close();
	}

}
