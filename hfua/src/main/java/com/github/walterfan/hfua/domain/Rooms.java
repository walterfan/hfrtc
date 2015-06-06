package com.github.walterfan.hfua.domain;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;

public class Rooms {
	private Collection<Room> rooms;
	
	public Rooms() {
		rooms = new LinkedList<Room>();
	}
	
	
	public Rooms(Collection<Room> rooms) {
		rooms = rooms;
	}


	public Collection<Room> getRooms() {
		return rooms;
	}


	public void setRooms(List<Room> rooms) {
		this.rooms = rooms;
	}
	


	
}
