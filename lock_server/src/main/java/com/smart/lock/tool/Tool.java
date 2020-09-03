package com.smart.lock.tool;

import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;

import org.apache.commons.io.IOUtils;

public class Tool {
	public static String exec_command(String... command) throws IOException, InterruptedException {
		ProcessBuilder processBuilder = new ProcessBuilder(command);
		processBuilder.redirectErrorStream(true);

		Process process = processBuilder.start();
		InputStream inputStream = process.getInputStream();
		String output = IOUtils.toString(inputStream, StandardCharsets.UTF_8);
		int exitCode = process.waitFor();
		if (0 != exitCode)
			throw new IOException("0 != exitCode");
		return output;
	}
}
