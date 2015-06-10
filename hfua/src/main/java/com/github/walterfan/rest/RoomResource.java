package com.github.walterfan.rest;

import javax.ws.rs.Consumes;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;


/**

GET /rooms：list all room
POST /rooms：create a room
GET /rooms/ID：retrieve a room
PUT /rooms/ID： update a room with all fields
PATCH /rooms/ID：update a room with part of fields
DELETE /rooms/ID：delete a room

* 
 * @author walter
 */
@Path("/api/v1/rooms")
public class RoomResource {
    
    //POST /rooms：create a room
	@POST
	@Consumes(MediaType.APPLICATION_JSON)
    public Response create() {
        return Response.ok().build();
    }
    
    //GET /rooms/ID：retrieve a room
    public Response read() {
        return Response.ok().build();
    }
    
    //PUT /rooms/ID： update a room with all fields
    //PATCH /rooms/ID：update a room with part of fields
    public Response update() {
        return Response.ok().build();
    }
    
    //DELETE /rooms/ID：delete a room
    public Response delete() {
        return Response.ok().build();
    }
    
    //GET /rooms：list all room
    public Response list() {
        return Response.ok().build();
    }
    
    //GET /rooms/search：search a room
    public Response search() {
        return Response.ok().build();
    }
}
