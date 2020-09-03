package com.smart.lock;

import com.smart.lock.tool.Encryption;
import com.smart.lock.tool.FaceRecognition;

public class Init {
	public static void init() throws Exception {
		if (!Encryption.init())
			throw new Exception("Initialize Encryption.init() failed!");
		if (!FaceRecognition.init())
			throw new Exception("Initialize FaceRecognition.init() failed!");
	}
}
