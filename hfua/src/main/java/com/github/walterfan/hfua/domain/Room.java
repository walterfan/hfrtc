package com.github.walterfan.hfua.domain;



import com.github.walterfan.devaid.domain.BaseObject;

public class Room extends BaseObject {
	/**
	 * 
	 */
	private static final long serialVersionUID = -6730442164062221232L;
	private String id;
	private String name;
	private String host;
	private String password;
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getHost() {
		return host;
	}
	public void setHost(String host) {
		this.host = host;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	

	
	
}
