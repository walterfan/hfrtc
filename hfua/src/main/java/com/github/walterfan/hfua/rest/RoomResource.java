package com.github.walterfan.hfua.rest;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.ws.rs.Consumes;
import javax.ws.rs.DELETE;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.PUT;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Response;

import com.github.walterfan.hfua.domain.Room;
/*
 * List: GET http://host/api/v1/rooms
 * Create: POST http://host/api/v1/rooms
 * Read: GET http://host/api/v1/room/333
 * Update: PUT http://host/api/v1/room/333
 * Delete: DELETE http://host/api/v1/room/333
 */
@Path("/api/v1/rooms")
public class RoomResource {
	private Map<String, Room> roomMap = new HashMap<String, Room>();
	
	public RoomResource() {
		Room room1 = new Room();
		room1.setName("The 1st Room");
		room1.setId("1");
		
		Room room2 = new Room();
		room2.setName("The 2nd Room");
		room2.setId("2");
		
		roomMap.put(room1.getId(), room1);
		roomMap.put(room2.getId(), room2);
	}

	@GET
	@Path("/")
	@Produces("application/json")
	public Collection<Room> list() {
		return roomMap.values();

	}
	
	
	@GET
	@Path("/{id}")
	@Produces("application/json")
	public Room retrieve(@PathParam("id") String roomID) {
		return roomMap.get(roomID); 
 
	}
 
	@POST
	@Path("/")
	@Consumes("application/json")
	public Response create(Room room) {
		String result = "created : " + room;
		return Response.status(201).entity(result).build();
 
	}
	
	@PUT
	@Path("/{id}")
	@Consumes("application/json")
	public Response update(@PathParam("id") String roomID) {
		String result = "updated : " + roomID;
		return Response.status(200).entity(result).build();
 
	}
	
	
	@Path("/{id}") 
	@DELETE 
	public Response delete(@PathParam("id") String roomID) 
	{ 
		roomMap.remove(roomID);
		String result = "{\"status\": \"success\"}"; 
		return Response.status(204).entity(result).build();
	} 
}