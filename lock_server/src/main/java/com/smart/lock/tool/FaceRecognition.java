package com.smart.lock.tool;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.smart.lock.Config;

public class FaceRecognition {
	private String python_filename;
	private String model_path;
	private String train_dir;
	private String info_path;

	private static FaceRecognition faceRecognition;

	public static boolean init() {
		faceRecognition = new FaceRecognition(Config.python_filename, Config.model_path, Config.train_dir,
				Config.info_path);
//		faceRecognition.train();
		return true;
	}

	public static MarkedImg _predict_and_mark(String base64_img) {
		return faceRecognition.predict_and_mark(base64_img);
	}

	public static class MarkedImg {
		public static class Info {
			private String id;
			private String name;
			private String type;
			private String safety;

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

			public String getType() {
				return type;
			}

			public void setType(String type) {
				this.type = type;
			}

			public String getSafety() {
				return safety;
			}

			public void setSafety(String safety) {
				this.safety = safety;
			}
		}

		private Info info;
		private String base64_img;

		public Info getInfo() {
			return info;
		}

		public void setInfo(Info info) {
			this.info = info;
		}

		MarkedImg() {
			this(null, null);
		}

		MarkedImg(Info info, String base64_img) {
			this.info = info;
			this.base64_img = base64_img;
		}

		public String getBase64_img() {
			return base64_img;
		}

		public void setBase64_img(String base64_img) {
			this.base64_img = base64_img;
		}
	}

	public FaceRecognition(String python_filename, String model_path, String train_dir, String info_path) {
		this.python_filename = python_filename;
		this.model_path = model_path;
		this.train_dir = train_dir;
		this.info_path = info_path;

	}

	public boolean train() {
		try {
			String train_result = Tool.exec_command(Config.python3_bin, python_filename, "train", train_dir,
					model_path);
			System.out.println(train_result);
		} catch (IOException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
		return true;
	}

	public MarkedImg predict_and_mark(String base64_img) {
		try {
			FileUtils.writeByteArrayToFile(new File(Config.temp_image_file), Encryption.decodeBase64(base64_img));
			String marked = Tool.exec_command(Config.python3_bin, python_filename, "mark", Config.temp_image_file,
					model_path, info_path);
			ObjectMapper mapper = new ObjectMapper();
			return mapper.readValue(marked, MarkedImg.class);
		} catch (IOException | InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
	}
}
