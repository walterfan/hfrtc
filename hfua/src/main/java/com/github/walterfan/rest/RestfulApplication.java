package com.github.walterfan.rest;

import java.util.HashSet;
import java.util.Set;

import javax.ws.rs.core.Application;

public class RestfulApplication extends Application {
	
	private static Set<Object> services = new HashSet<Object>();

	public RestfulApplication() {
		services.add(new RoomResource());
	}

	@Override
	public Set<Object> getSingletons() {
		return services;
	}

	public static Set<Object> getServices() {
		return services;
	}
}