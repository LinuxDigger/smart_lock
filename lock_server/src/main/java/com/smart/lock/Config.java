package com.smart.lock;

public class Config {
	public static long timeout = 10 * 1000;
//	public static int PBKDF2Round = 65563;
	public static int PBKDF2Round = 131;
//	public static String python_filename = "/a/project/smart_lock/face_recognition/face_recognition_knn.py";
//	public static String model_path = "/a/project/smart_lock/face_recognition/trained_knn_model.clf";
//	public static String info_path = "/a/project/smart_lock/face_recognition/info.json";
//	public static String train_dir = "/a/project/smart_lock/face_recognition/train/";
//	public static String python3_bin = "/a/bin/python3";
//	public static String temp_image_file = "/t/temp_image";
	
	

	public static String python_filename = "/home/davies/smark_lock/face_recognition/face_recognition_knn.py";
	public static String model_path = "/home/davies/smark_lock/face_recognition/trained_knn_model.clf";
	public static String info_path = "/home/davies/smark_lock/face_recognition/info.json";
	public static String train_dir = "/home/davies/smark_lock/face_recognition/train/";
	public static String python3_bin = "/usr/bin/python3";
	public static String temp_image_file = "/home/davies/smark_lock/temp_image";
}
