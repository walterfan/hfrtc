package com.github.walterfan.hfua.rest;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import javax.ws.rs.core.Application;
/*
 * refer to https://github.com/resteasy/Resteasy/blob/master/jaxrs/jaxrs-api/src/main/java
 * 					javax/ws/rs/core/Application.java
 */


public class RestfulApplication extends Application {
	
	private Set<Object> singletons = new HashSet<Object>();
	private Set<Class<?>> classes = new HashSet<Class<?>>();

	public RestfulApplication() {
		//classes.add(RoomResource.class);
		singletons.add(new RoomResource());
	}

	@Override
	public Set<Class<?>> getClasses() {
		return classes;
	}

	@Override
	public Set<Object> getSingletons() {
		return singletons;
	}

}
