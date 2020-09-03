package com.smart.lock.controller.api.json;

public class Status {
	private int status;
	private String error;
	private String info;

	public Status(int status, String error, String info) {
		this.status = status;
		this.error = error;
		this.info = info;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public String getError() {
		return error;
	}

	public void setError(String error) {
		this.error = error;
	}

	public String getInfo() {
		return info;
	}

	public void setInfo(String info) {
		this.info = info;
	}
}
