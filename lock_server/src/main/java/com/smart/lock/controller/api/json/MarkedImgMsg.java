package com.smart.lock.controller.api.json;

import java.util.List;

import com.smart.lock.tool.FaceRecognition.MarkedImg;

public class MarkedImgMsg {
	private String type;
	private List<MarkedImg> data;

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}

	public List<MarkedImg> getData() {
		return data;
	}

	public void setData(List<MarkedImg> data) {
		this.data = data;
	}

}
