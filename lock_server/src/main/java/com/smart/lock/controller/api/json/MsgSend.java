package com.smart.lock.controller.api.json;

import java.util.List;

public class MsgSend {
	private String from;
	private List<String> to;
	private boolean mark_image;
	private String msg;

	public String getFrom() {
		return from;
	}

	public void setFrom(String from) {
		this.from = from;
	}

	public List<String> getTo() {
		return to;
	}

	public void setTo(List<String> to) {
		this.to = to;
	}

	public boolean isMark_image() {
		return mark_image;
	}

	public void setMark_image(boolean mark_image) {
		this.mark_image = mark_image;
	}

	public String getMsg() {
		return msg;
	}

	public void setMsg(String msg) {
		this.msg = msg;
	}

}
