package com.smart.lock.controller.api;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.TimeUnit;

import org.springframework.http.MediaType;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.context.request.async.DeferredResult;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.smart.lock.controller.api.json.MarkedImgMsg;
import com.smart.lock.controller.api.json.MsgGet;
import com.smart.lock.controller.api.json.MsgSend;
import com.smart.lock.controller.api.json.Status;
import com.smart.lock.tool.FaceRecognition;
import com.smart.lock.tool.FaceRecognition.MarkedImg;

@Controller
@RequestMapping("/msg")

public class Msg {

	private long timeOutInMilliSec = 60 * 1000;
	private MsgGet timeout_response = new MsgGet(1, null, null);
	private MsgGet error_response = new MsgGet(2, null, null);

	private HashMap<String, DeferredResult<MsgGet>> get_list = new HashMap<String, DeferredResult<MsgGet>>();

	@RequestMapping(value = "/get", produces = MediaType.APPLICATION_JSON_VALUE)
	@ResponseBody
	DeferredResult<MsgGet> get(String id) {
		if (null == id || id.isEmpty()) {
			return null;
		}
		synchronized (get_list) {
			if (get_list.containsKey(id)) {
				DeferredResult<MsgGet> deferredResult = get_list.get(id);
				if (!deferredResult.isSetOrExpired()) {
					deferredResult.setResult(error_response);
				}
			}
		}
		DeferredResult<MsgGet> deferredResult = new DeferredResult<>(timeOutInMilliSec, timeout_response);
		deferredResult.onCompletion(new Runnable() {
			@Override
			public void run() {
				synchronized (get_list) {
					boolean result = get_list.remove(id, deferredResult);
				}
			}
		});
		synchronized (get_list) {
			get_list.put(id, deferredResult);
		}
		return deferredResult;
	}

	@RequestMapping(value = "/send", produces = MediaType.APPLICATION_JSON_VALUE)
	@ResponseBody
	Status send(@RequestBody MsgSend msg_send) {
		String from = msg_send.getFrom();
		List<String> to = msg_send.getTo();
		String msg = msg_send.getMsg();
		if (null == from) {
			return new Status(-1, "null == from", null);
		}
		if (null == to || to.isEmpty()) {
			return new Status(-1, "null == to || to.isEmpty()", null);
		}
		if (msg_send.isMark_image()) {
			ObjectMapper mapper = new ObjectMapper();
			MarkedImgMsg markedImgMsg = null;
			try {
				markedImgMsg = mapper.readValue(msg_send.getMsg(), MarkedImgMsg.class);
				MarkedImg _markedImg = FaceRecognition._predict_and_mark(markedImgMsg.getData().get(0).getBase64_img());
				if (null != _markedImg) {
					markedImgMsg.getData().set(0, _markedImg);
					msg = mapper.writeValueAsString(markedImgMsg);
				}
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		int total_send = 0;
		MsgGet _msg = new MsgGet(0, from, msg);
		for (String i : to) {
			int count = 0;
			while (!get_list.containsKey(i) && ++count < 10) {
				try {
					TimeUnit.MILLISECONDS.sleep(100);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
			if (get_list.containsKey(i)) {
				DeferredResult<MsgGet> deferredResult = get_list.remove(i);
				if (deferredResult.setResult(_msg))
					++total_send;
			}
		}
		return new Status(0, null, String.format("%d user send", total_send));
	}
}
