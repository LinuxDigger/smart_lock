package com.smart.lock.controller.api;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.nio.charset.StandardCharsets;
import java.security.KeyPair;
import java.security.SecureRandom;
import java.util.Arrays;
import java.util.Collection;
import java.util.Date;
import java.util.Enumeration;
import java.util.HashMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.Part;

import org.apache.commons.codec.binary.Hex;
import org.apache.commons.io.IOUtils;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import com.smart.lock.Config;
import com.smart.lock.model.EncryptedData;
import com.smart.lock.model.TestData;
import com.smart.lock.tool.Encryption;

@Controller
@RequestMapping("/test")
public class Test {
	@RequestMapping("/protocol")
	@ResponseBody
	public TestData protocol(HttpServletRequest request) {
		TestData testData = new TestData();
		try {
			testData.setMethod(request.getMethod());
			testData.setAuthType(request.getAuthType());
			testData.setCharacterEncoding(request.getCharacterEncoding());
			testData.setContentLengthLong(request.getContentLengthLong());
			testData.setContentType(request.getContentType());
			testData.setLocalAddr(request.getLocalAddr());
			testData.setLocale(request.getLocale().toString());
			testData.setLocalName(request.getLocalName());
			testData.setLocalPort(request.getLocalPort());
			testData.setMethod(request.getMethod());
			testData.setProtocol(request.getProtocol());
			testData.setQueryString(request.getQueryString());
			testData.setRemoteAddr(request.getRemoteAddr());
			testData.setRemoteHost(request.getRemoteHost());
			testData.setRemotePort(request.getRemotePort());
			testData.setRemoteUser(request.getRemoteUser());
			testData.setRequestURI(request.getRequestURI());
			testData.setScheme(request.getScheme());
			testData.setParameterMap(request.getParameterMap());
			testData.setCookies(request.getCookies());

			HashMap<String, String> headers = new HashMap<String, String>();
			Enumeration<String> names = request.getHeaderNames();
			if (null != names)
				while (names.hasMoreElements()) {
					String name = names.nextElement();
					headers.put(name, request.getHeader(name));
				}
			testData.setHeaders(headers);

			String contentType = request.getHeader("Content-Type");
			if (null != contentType && contentType.startsWith("multipart/form-data;")) {
				HashMap<String, TestData.Part> parts = new HashMap<String, TestData.Part>();
				Collection<Part> _parts = request.getParts();
				for (Part part : _parts) {
					String name = part.getName();
					HashMap<String, String> partHeaders = new HashMap<String, String>();
					for (String headerName : part.getHeaderNames()) {
						partHeaders.put(headerName, part.getHeader(headerName));
					}
					String data = IOUtils.toString(part.getInputStream(), "utf8");
					TestData.Part _part = new TestData.Part();
					_part.setName(part.getName());
					_part.setHeaders(partHeaders);
					_part.setContentType(part.getContentType());
					_part.setSize(part.getSize());
					_part.setSubmittedFileName(part.getSubmittedFileName());
					_part.setData(data);
					parts.put(name, _part);
				}
				testData.setParts(parts);
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			testData.setError(e.toString());
		}

		return testData;
	}

	@RequestMapping("/get_id")
	@ResponseBody
	public String get_id(HttpServletRequest request) {
		SecureRandom random = new SecureRandom();
		byte[] bytes = new byte[16];
		random.nextBytes(bytes);
		return Hex.encodeHexString(bytes);
	}

	// 证书，和我发你们的是一样的。
	private static byte[] credential = new byte[] { (byte) 0xEE, (byte) 0xFD, (byte) 0x3F, (byte) 0x7E, (byte) 0xBC,
			(byte) 0x81, (byte) 0x32, (byte) 0xA3, (byte) 0xDA, (byte) 0xAC, (byte) 0xAF, (byte) 0xCD, (byte) 0x0B,
			(byte) 0x8B, (byte) 0x3F, (byte) 0x6A, (byte) 0x22, (byte) 0x5F, (byte) 0xFB, (byte) 0x4E, (byte) 0xF1,
			(byte) 0xE5, (byte) 0xBD, (byte) 0x5F, (byte) 0x00, (byte) 0x18, (byte) 0x38, (byte) 0xFC, (byte) 0x5B,
			(byte) 0xEB, (byte) 0x0F, (byte) 0x1A, (byte) 0xD5, (byte) 0x45, (byte) 0x64, (byte) 0xBB, (byte) 0x75,
			(byte) 0xB8, (byte) 0x82, (byte) 0x9C, (byte) 0x59, (byte) 0x83, (byte) 0x6F, (byte) 0x97, (byte) 0x2F,
			(byte) 0x1E, (byte) 0xF0, (byte) 0x61, (byte) 0xEB, (byte) 0x41, (byte) 0x18, (byte) 0xC0, (byte) 0xDE,
			(byte) 0xDF, (byte) 0xA5, (byte) 0xF8, (byte) 0x7C, (byte) 0x1D, (byte) 0x0A, (byte) 0x7A, (byte) 0x11,
			(byte) 0xE5, (byte) 0xB2, (byte) 0xA1, (byte) 0xB2, (byte) 0x76, (byte) 0x63, (byte) 0x0D, (byte) 0xB0,
			(byte) 0xC6, (byte) 0xE6, (byte) 0xF9, (byte) 0xF9, (byte) 0x69, (byte) 0x22, (byte) 0x19, (byte) 0x3E,
			(byte) 0x7F, (byte) 0x84, (byte) 0x8D, (byte) 0xFD, (byte) 0xB8, (byte) 0x34, (byte) 0xB6, (byte) 0x7A,
			(byte) 0xFC, (byte) 0x7D, (byte) 0x98, (byte) 0xCC, (byte) 0xFF, (byte) 0x50, (byte) 0xB1, (byte) 0x3B,
			(byte) 0x98, (byte) 0xCE, (byte) 0x7F, (byte) 0xAC, (byte) 0x79, (byte) 0x76, (byte) 0xF3, (byte) 0x06,
			(byte) 0x1E, (byte) 0x18, (byte) 0x77, (byte) 0xA5, (byte) 0x2F, (byte) 0x34, (byte) 0x19, (byte) 0x72,
			(byte) 0xA5, (byte) 0xF4, (byte) 0x86, (byte) 0x2B, (byte) 0xD3, (byte) 0x7B, (byte) 0xB8, (byte) 0x00,
			(byte) 0x61, (byte) 0x07, (byte) 0xB6, (byte) 0xF5, (byte) 0x6F, (byte) 0xE1, (byte) 0xBA, (byte) 0x50,
			(byte) 0x1F, (byte) 0x6B, (byte) 0xF4, (byte) 0xBB, (byte) 0x55, (byte) 0xA0, (byte) 0x6F, (byte) 0x64,
			(byte) 0x4B, (byte) 0xFA, (byte) 0x5F, (byte) 0xAD, (byte) 0x30, (byte) 0x10, (byte) 0xF0, (byte) 0x04,
			(byte) 0xC9, (byte) 0xD5, (byte) 0x76, (byte) 0x29, (byte) 0xF6, (byte) 0xFE, (byte) 0x84, (byte) 0x27,
			(byte) 0x0B, (byte) 0xDF, (byte) 0x04, (byte) 0x35, (byte) 0x1B, (byte) 0x45, (byte) 0xC7, (byte) 0xE5,
			(byte) 0x0A, (byte) 0x7B, (byte) 0x4C, (byte) 0x49, (byte) 0x6A, (byte) 0xE2, (byte) 0xB2, (byte) 0x72,
			(byte) 0xF5, (byte) 0x12, (byte) 0x27, (byte) 0xF5, (byte) 0x4A, (byte) 0x26, (byte) 0x6F, (byte) 0xAF,
			(byte) 0x76, (byte) 0x5A, (byte) 0x04, (byte) 0x45, (byte) 0x40, (byte) 0xB6, (byte) 0x2A, (byte) 0xD8,
			(byte) 0x5B, (byte) 0x01, (byte) 0x78, (byte) 0x8B, (byte) 0x9F, (byte) 0x1E, (byte) 0x7E, (byte) 0xD1,
			(byte) 0x29, (byte) 0xB1, (byte) 0xB1, (byte) 0xA5, (byte) 0x5B, (byte) 0xA9, (byte) 0xDD, (byte) 0xB9,
			(byte) 0x02, (byte) 0x85, (byte) 0x05, (byte) 0xF8, (byte) 0x76, (byte) 0x0C, (byte) 0x7C, (byte) 0xB2,
			(byte) 0x18, (byte) 0xDD, (byte) 0x2D, (byte) 0x58, (byte) 0x67, (byte) 0xFA, (byte) 0xCB, (byte) 0x1E,
			(byte) 0x60, (byte) 0x56, (byte) 0x6C, (byte) 0x92, (byte) 0x51, (byte) 0x11, (byte) 0x8A, (byte) 0x07,
			(byte) 0xB4, (byte) 0x0E, (byte) 0xF3, (byte) 0xAD, (byte) 0x18, (byte) 0x1D, (byte) 0x77, (byte) 0x53,
			(byte) 0x14, (byte) 0x09, (byte) 0x43, (byte) 0x98, (byte) 0xD0, (byte) 0xBA, (byte) 0x1F, (byte) 0x89,
			(byte) 0xE1, (byte) 0xD8, (byte) 0xF4, (byte) 0x6F, (byte) 0x1B, (byte) 0xEE, (byte) 0xC0, (byte) 0xD1,
			(byte) 0x04, (byte) 0xB8, (byte) 0x2B, (byte) 0xDD, (byte) 0x59, (byte) 0xD6, (byte) 0x7B, (byte) 0xA4,
			(byte) 0x82, (byte) 0xB1, (byte) 0x3C, (byte) 0x92, (byte) 0x6E, (byte) 0x66, (byte) 0x75, (byte) 0xEA,
			(byte) 0x82, (byte) 0x6E, (byte) 0x79, (byte) 0x58, (byte) 0x8A, (byte) 0x4E, (byte) 0xF8, (byte) 0x7D,
			(byte) 0x7B, (byte) 0x62, (byte) 0xE2, (byte) 0x12, (byte) 0x3E, (byte) 0xBC, (byte) 0x14, (byte) 0xB5,
			(byte) 0xBA, (byte) 0x80, (byte) 0x18, (byte) 0xD3, (byte) 0x5B, (byte) 0x99, (byte) 0xB8, (byte) 0xE2,
			(byte) 0x9E, (byte) 0xF2, (byte) 0x7D, (byte) 0xB7, (byte) 0x2D, (byte) 0x60, (byte) 0xA3, (byte) 0x16,
			(byte) 0x19, (byte) 0x90, (byte) 0xEE, (byte) 0xDC, (byte) 0xCC, (byte) 0xF9, (byte) 0xA6, (byte) 0xF8,
			(byte) 0xF4, (byte) 0x96, (byte) 0x95, (byte) 0xC5, (byte) 0x35, (byte) 0x88, (byte) 0xB1, (byte) 0x76,
			(byte) 0xFA, (byte) 0xEA, (byte) 0xBD, (byte) 0x4D, (byte) 0xE2, (byte) 0xF2, (byte) 0x64, (byte) 0xEB,
			(byte) 0x52, (byte) 0x2A, (byte) 0x33, (byte) 0x52, (byte) 0xCF, (byte) 0x9B, (byte) 0x01, (byte) 0x4D,
			(byte) 0xF5, (byte) 0xE9, (byte) 0x22, (byte) 0xA3, (byte) 0x49, (byte) 0x28, (byte) 0x37, (byte) 0xF7,
			(byte) 0x56, (byte) 0x78, (byte) 0x24, (byte) 0xA7, (byte) 0x64, (byte) 0xC4, (byte) 0x4E, (byte) 0xAC,
			(byte) 0xE2, (byte) 0xC0, (byte) 0x12, (byte) 0x0D, (byte) 0xD2, (byte) 0x03, (byte) 0xFF, (byte) 0x94,
			(byte) 0x21, (byte) 0x7C, (byte) 0xD1, (byte) 0x1B, (byte) 0x8B, (byte) 0xAC, (byte) 0xE0, (byte) 0x36,
			(byte) 0x7E, (byte) 0xFE, (byte) 0x82, (byte) 0x4C, (byte) 0xFD, (byte) 0xA6, (byte) 0x17, (byte) 0x20,
			(byte) 0x73, (byte) 0x98, (byte) 0x53, (byte) 0x15, (byte) 0x46, (byte) 0xA5, (byte) 0x2A, (byte) 0xC8,
			(byte) 0x89, (byte) 0x76, (byte) 0xB5, (byte) 0xB5, (byte) 0xD3, (byte) 0x10, (byte) 0x85, (byte) 0xD0,
			(byte) 0x72, (byte) 0x3C, (byte) 0x3F, (byte) 0x85, (byte) 0x54, (byte) 0x14, (byte) 0xF8, (byte) 0x9B,
			(byte) 0xF1, (byte) 0x61, (byte) 0xBF, (byte) 0xB9, (byte) 0x10, (byte) 0xF5, (byte) 0x3A, (byte) 0xD0,
			(byte) 0xD9, (byte) 0xDF, (byte) 0x78, (byte) 0x16, (byte) 0x05, (byte) 0xAD, (byte) 0x21, (byte) 0x7A,
			(byte) 0xE9, (byte) 0xC7, (byte) 0x35, (byte) 0xE3, (byte) 0xED, (byte) 0xDB, (byte) 0x90, (byte) 0xA6,
			(byte) 0xB4, (byte) 0x1F, (byte) 0x3C, (byte) 0xF2, (byte) 0x74, (byte) 0xC6, (byte) 0x4C, (byte) 0x74,
			(byte) 0x06, (byte) 0x19, (byte) 0xA9, (byte) 0x3B, (byte) 0x66, (byte) 0x46, (byte) 0x18, (byte) 0x4D,
			(byte) 0xD9, (byte) 0xE8, (byte) 0x5C, (byte) 0xF9, (byte) 0xFB, (byte) 0x68, (byte) 0x7B, (byte) 0x01,
			(byte) 0xA0, (byte) 0x66, (byte) 0x05, (byte) 0x30, (byte) 0xED, (byte) 0x99, (byte) 0xDC, (byte) 0x8D,
			(byte) 0xA8, (byte) 0x4B, (byte) 0xEB, (byte) 0xB6, (byte) 0x06, (byte) 0x85, (byte) 0x5B, (byte) 0x8E,
			(byte) 0xE7, (byte) 0xBD, (byte) 0x0A, (byte) 0x70, (byte) 0x68, (byte) 0x7C, (byte) 0xA7, (byte) 0xF3,
			(byte) 0x60, (byte) 0xCC, (byte) 0x09, (byte) 0xD3, (byte) 0xC9, (byte) 0x13, (byte) 0x7F, (byte) 0x87,
			(byte) 0x92, (byte) 0x56, (byte) 0xAD, (byte) 0x8D, (byte) 0xA7, (byte) 0xB8, (byte) 0xAD, (byte) 0xE5,
			(byte) 0x7D, (byte) 0xC9, (byte) 0x96, (byte) 0xB9, (byte) 0xD6, (byte) 0xE9, (byte) 0xF2, (byte) 0x17,
			(byte) 0x5B, (byte) 0x6C, (byte) 0x00, (byte) 0x44, (byte) 0x3D, (byte) 0x70, (byte) 0x55, (byte) 0x3E,
			(byte) 0x56, (byte) 0x24, (byte) 0xB3, (byte) 0x88, (byte) 0x8E, (byte) 0xA2, (byte) 0x98, (byte) 0x41,
			(byte) 0x09, (byte) 0x6D, (byte) 0xE1, (byte) 0x12, (byte) 0x73, (byte) 0x03, (byte) 0x23, (byte) 0x4B,
			(byte) 0xD1, (byte) 0xE5, (byte) 0x98, (byte) 0x20, (byte) 0x5B, (byte) 0x27, (byte) 0xDA, (byte) 0xEB,
			(byte) 0xA1, (byte) 0xDA, (byte) 0x4F, (byte) 0xBB, (byte) 0x98, (byte) 0x24, (byte) 0xB7, (byte) 0x02,
			(byte) 0x8C, (byte) 0xE9, (byte) 0x8E, (byte) 0xFA, (byte) 0xF9, (byte) 0xD1, (byte) 0x92, (byte) 0xE3,
			(byte) 0xDE, (byte) 0x02, (byte) 0x16, (byte) 0x90, (byte) 0xFF, (byte) 0x4B, (byte) 0x61, (byte) 0xFB,
			(byte) 0x1B, (byte) 0xA3, (byte) 0x3E, (byte) 0x19, (byte) 0x32, (byte) 0xBA, (byte) 0xE9, (byte) 0x13,
			(byte) 0xDF, (byte) 0xB7, (byte) 0x0B, (byte) 0x80, (byte) 0x82, (byte) 0xD4, (byte) 0xB1, (byte) 0x32,
			(byte) 0xD9, (byte) 0x87, (byte) 0x32, (byte) 0xEF, (byte) 0xBE, (byte) 0x61, (byte) 0x09, (byte) 0xC9,
			(byte) 0x8F, (byte) 0x33, (byte) 0xBD, (byte) 0x62, (byte) 0xAD, (byte) 0x2D, (byte) 0x81, (byte) 0xAA,
			(byte) 0xE8, (byte) 0x00, (byte) 0xFA, (byte) 0xF6, (byte) 0x46, (byte) 0x7E, (byte) 0x76, (byte) 0xF7,
			(byte) 0xE9, (byte) 0x4A, (byte) 0x94, (byte) 0x29, (byte) 0x42, (byte) 0x55, (byte) 0x14, (byte) 0x16,
			(byte) 0xC3, (byte) 0xA6, (byte) 0x25, (byte) 0xB2, (byte) 0xA2, (byte) 0x2B, (byte) 0x27, (byte) 0x19,
			(byte) 0xA6, (byte) 0x98, (byte) 0x44, (byte) 0x5A, (byte) 0x35, (byte) 0x0E, (byte) 0x4D, (byte) 0x7D,
			(byte) 0x17, (byte) 0x3C, (byte) 0x0D, (byte) 0x78, (byte) 0x84, (byte) 0xA8, (byte) 0x60, (byte) 0xDF,
			(byte) 0x11, (byte) 0x40, (byte) 0x06, (byte) 0xC9, (byte) 0x98, (byte) 0x86, (byte) 0x89, (byte) 0x1C,
			(byte) 0x02, (byte) 0x44, (byte) 0x49, (byte) 0xBC, (byte) 0xCA, (byte) 0x53, (byte) 0x73, (byte) 0xDE,
			(byte) 0xB7, (byte) 0xA4, (byte) 0x68, (byte) 0x89, (byte) 0x2A, (byte) 0x31, (byte) 0xDB, (byte) 0xA7,
			(byte) 0x42, (byte) 0x85, (byte) 0x73, (byte) 0xAA, (byte) 0xAC, (byte) 0xA3, (byte) 0x03, (byte) 0x70,
			(byte) 0x3A, (byte) 0xBF, (byte) 0x22, (byte) 0x54, (byte) 0x32, (byte) 0xB9, (byte) 0xAF, (byte) 0xBF,
			(byte) 0x22, (byte) 0xC8, (byte) 0xCD, (byte) 0xC8, (byte) 0x93, (byte) 0x5F, (byte) 0xDF, (byte) 0x11,
			(byte) 0x2D, (byte) 0xB9, (byte) 0x5D, (byte) 0x16, (byte) 0xE4, (byte) 0x55, (byte) 0x17, (byte) 0x1C,
			(byte) 0xBD, (byte) 0x7D, (byte) 0xE0, (byte) 0x61, (byte) 0xAA, (byte) 0x6F, (byte) 0x01, (byte) 0xFE,
			(byte) 0xB0, (byte) 0xF9, (byte) 0x90, (byte) 0xD0, (byte) 0x33, (byte) 0x88, (byte) 0x7B, (byte) 0xB3,
			(byte) 0x38, (byte) 0xA1, (byte) 0xAB, (byte) 0x99, (byte) 0xEA, (byte) 0x85, (byte) 0x8B, (byte) 0x55,
			(byte) 0x02, (byte) 0xC1, (byte) 0x90, (byte) 0x9A, (byte) 0x32, (byte) 0x00, (byte) 0x4C, (byte) 0xA7,
			(byte) 0x6F, (byte) 0x7D, (byte) 0x51, (byte) 0xE0, (byte) 0xE7, (byte) 0x83, (byte) 0x0C, (byte) 0xCC,
			(byte) 0x15, (byte) 0x3F, (byte) 0xC9, (byte) 0xE0, (byte) 0xD4, (byte) 0x4F, (byte) 0xD1, (byte) 0x99,
			(byte) 0xA3, (byte) 0x36, (byte) 0xB8, (byte) 0xAE, (byte) 0x4F, (byte) 0x80, (byte) 0x15, (byte) 0x97,
			(byte) 0x17, (byte) 0xAF, (byte) 0xC4, (byte) 0xF8, (byte) 0xC6, (byte) 0xAC, (byte) 0xE0, (byte) 0x9F,
			(byte) 0x5C, (byte) 0xF8, (byte) 0xFF, (byte) 0xF4, (byte) 0xA7, (byte) 0x21, (byte) 0x72, (byte) 0x9E,
			(byte) 0xDA, (byte) 0x8B, (byte) 0xE6, (byte) 0xB5, (byte) 0xA3, (byte) 0x26, (byte) 0x51, (byte) 0xAE,
			(byte) 0xF7, (byte) 0x7F, (byte) 0x88, (byte) 0xDB, (byte) 0xD5, (byte) 0x52, (byte) 0x4C, (byte) 0xA6,
			(byte) 0xA1, (byte) 0xC6, (byte) 0xE0, (byte) 0x04, (byte) 0x25, (byte) 0x5F, (byte) 0xDB, (byte) 0x3D,
			(byte) 0x89, (byte) 0x5B, (byte) 0x05, (byte) 0x6A, (byte) 0x34, (byte) 0x61, (byte) 0x42, (byte) 0xAF,
			(byte) 0xB6, (byte) 0x45, (byte) 0x18, (byte) 0xF6, (byte) 0xD2, (byte) 0xCE, (byte) 0xD8, (byte) 0xCD,
			(byte) 0x06, (byte) 0xD2, (byte) 0x71, (byte) 0xF1, (byte) 0x67, (byte) 0x0F, (byte) 0xBA, (byte) 0x80,
			(byte) 0x39, (byte) 0x2F, (byte) 0xD0, (byte) 0x65, (byte) 0x7F, (byte) 0x35, (byte) 0xC5, (byte) 0x58,
			(byte) 0x87, (byte) 0xCE, (byte) 0xCF, (byte) 0xE0, (byte) 0x8F, (byte) 0xDD, (byte) 0xBD, (byte) 0x23,
			(byte) 0x51, (byte) 0x3E, (byte) 0xD6, (byte) 0x4E, (byte) 0x0E, (byte) 0x55, (byte) 0x8E, (byte) 0x72,
			(byte) 0x23, (byte) 0xE8, (byte) 0x85, (byte) 0x4C, (byte) 0x57, (byte) 0xD2, (byte) 0x20, (byte) 0x47,
			(byte) 0x80, (byte) 0xE0, (byte) 0xE7, (byte) 0xC3, (byte) 0x11, (byte) 0xA8, (byte) 0x2C, (byte) 0x41,
			(byte) 0x7C, (byte) 0xCF, (byte) 0x15, (byte) 0x50, (byte) 0x4C, (byte) 0xCE, (byte) 0xF9, (byte) 0x9B,
			(byte) 0x20, (byte) 0x7D, (byte) 0xCC, (byte) 0x34, (byte) 0x21, (byte) 0xC0, (byte) 0x8A, (byte) 0x1F,
			(byte) 0x5C, (byte) 0xBE, (byte) 0x1B, (byte) 0xD1, (byte) 0xBC, (byte) 0xB1, (byte) 0xFE, (byte) 0x92,
			(byte) 0x23, (byte) 0x61, (byte) 0x1D, (byte) 0xA2, (byte) 0x03, (byte) 0xFF, (byte) 0x75, (byte) 0x82,
			(byte) 0xCA, (byte) 0x31, (byte) 0x44, (byte) 0xD9, (byte) 0x1F, (byte) 0x88, (byte) 0xE8, (byte) 0xE6,
			(byte) 0x64, (byte) 0xB8, (byte) 0x8D, (byte) 0xEF, (byte) 0x61, (byte) 0xD8, (byte) 0x0A, (byte) 0x0A,
			(byte) 0xC0, (byte) 0x62, (byte) 0x67, (byte) 0x3E, (byte) 0x1D, (byte) 0x54, (byte) 0x58, (byte) 0xA3,
			(byte) 0xCB, (byte) 0xA5, (byte) 0xEF, (byte) 0x60, (byte) 0x5C, (byte) 0xE6, (byte) 0x73, (byte) 0xBF,
			(byte) 0x22, (byte) 0x3E, (byte) 0x58, (byte) 0x66, (byte) 0x31, (byte) 0x83, (byte) 0xDB, (byte) 0x87,
			(byte) 0xFD, (byte) 0xC4, (byte) 0xE4, (byte) 0xF2, (byte) 0x8B, (byte) 0xBC, (byte) 0x7F, (byte) 0xCA,
			(byte) 0xB4, (byte) 0xE5, (byte) 0xC7, (byte) 0x2D, (byte) 0x14, (byte) 0x3F, (byte) 0x75, (byte) 0xCC,
			(byte) 0x62, (byte) 0xB0, (byte) 0x10, (byte) 0x1E, (byte) 0xE4, (byte) 0x5A, (byte) 0xFA, (byte) 0x5E,
			(byte) 0x34, (byte) 0x6B, (byte) 0x13, (byte) 0x4D, (byte) 0x58, (byte) 0xB1, (byte) 0xE9, (byte) 0x9E,
			(byte) 0x34, (byte) 0xC5, (byte) 0xF6, (byte) 0xB4, (byte) 0x81, (byte) 0x9D, (byte) 0x66, (byte) 0x25,
			(byte) 0xD6, (byte) 0xD6, (byte) 0xDE, (byte) 0x8A, (byte) 0x30, (byte) 0x15, (byte) 0x28, (byte) 0xC4,
			(byte) 0xDE, (byte) 0x50, (byte) 0x6E, (byte) 0x8C, (byte) 0xDC, (byte) 0xB2, (byte) 0x26, (byte) 0xF8,
			(byte) 0xEE, (byte) 0x8D, (byte) 0x1E, (byte) 0x1F, (byte) 0x84, (byte) 0x96, (byte) 0xD6, (byte) 0xF8,
			(byte) 0xB1, (byte) 0x39, (byte) 0x31, (byte) 0xB0, (byte) 0x46, (byte) 0x30, (byte) 0xB7, (byte) 0x15,
			(byte) 0x6B, (byte) 0xF0, (byte) 0x49, (byte) 0x17, (byte) 0xCC, (byte) 0x92, (byte) 0xF4, (byte) 0x56,
			(byte) 0x3C, (byte) 0x08, (byte) 0x77, (byte) 0x7A, (byte) 0x62, (byte) 0x4D, (byte) 0x84, (byte) 0x7A,
			(byte) 0xBF, (byte) 0x1C, (byte) 0xE1, (byte) 0xAB, (byte) 0x77, (byte) 0xC7, (byte) 0x93, (byte) 0xF7,
			(byte) 0xDD, (byte) 0xF8, (byte) 0x64, (byte) 0xEE, (byte) 0xAC, (byte) 0xF5, (byte) 0xF9, (byte) 0xAE,
			(byte) 0x40, (byte) 0x85, (byte) 0x1B, (byte) 0xEA, (byte) 0xF1, (byte) 0x45, (byte) 0xA5, (byte) 0x66,
			(byte) 0xD9, (byte) 0x76, (byte) 0x6B, (byte) 0xAE, (byte) 0x22, (byte) 0x59, (byte) 0xD8, (byte) 0x05,
			(byte) 0xB8, (byte) 0xE5, (byte) 0x84 };

	private static String IMEI = "415359522081115";

	// 这个ID没有用，用的ID是你上传的ID。
	private static String ID = "3CD679DBC30DA695C321E2D55EFDD695";

	public static class EnDecryptResult {

		// 包类型
		private String type;
		// 任务类型，加密或者解密
		private String taskType;
		// 你上传的时间戳
		private long timestamp;
		// 你上传的ID 锁或者客户端的
		private String ID;
		// 计算出的AES密匙
		private String AESKey;
		// 你上传的数据，**注意，不论是加密还是解密，你上传的数据都是base64编码过后的数据。
		private String postedData;
		// 解密结果，结果会转换为字符串返回给你。
		private String decryptedData;
		// 加密结果，base64编码
		private String encryptedData;
		// 你上传的hash值，如果和我解密过后计算的结果不一致会返回错误，base64编码。
		private String postedHash;
		// 我解密数据过后计算出来的hash，base64编码。
		private String calculatedHash;
		// 加密/解密过程中所有的错误都放在这里。
		private String error;

		public String getType() {
			return type;
		}

		public void setType(String type) {
			this.type = type;
		}

		public String getTaskType() {
			return taskType;
		}

		public void setTaskType(String taskType) {
			this.taskType = taskType;
		}

		public long getTimestamp() {
			return timestamp;
		}

		public void setTimestamp(long timestamp) {
			this.timestamp = timestamp;
		}

		public String getID() {
			return ID;
		}

		public void setID(String ID) {
			this.ID = ID;
		}

		public String getAESKey() {
			return AESKey;
		}

		public void setAESKey(String AESKey) {
			this.AESKey = AESKey;
		}

		public String getPostedData() {
			return postedData;
		}

		public void setPostedData(String postedData) {
			this.postedData = postedData;
		}

		public String getDecryptedData() {
			return decryptedData;
		}

		public void setDecryptedData(String decryptedData) {
			this.decryptedData = decryptedData;
		}

		public String getEncryptedData() {
			return encryptedData;
		}

		public void setEncryptedData(String encryptedData) {
			this.encryptedData = encryptedData;
		}

		public String getPostedHash() {
			return postedHash;
		}

		public void setPostedHash(String postedHash) {
			this.postedHash = postedHash;
		}

		public String getCalculatedHash() {
			return calculatedHash;
		}

		public void setCalculatedHash(String calculatedHash) {
			this.calculatedHash = calculatedHash;
		}

		public String getError() {
			return error;
		}

		public void setError(String error) {
			this.error = error;
		}
	}

	// 加密和解密两个函数都会把你上传的数据全部返回给你，方便你比对你传输上来的数据是否正确。
	// 加密/解密结果的error字段表示错误，如果加密/解密过程有错误，错误信息会放在error字段。
	// 解密结果和中间数据都会一起返回给你，你可以对比到哪一步出问题了，如果不是你的算法问题，或者你无法解决，可以让我来调试。
	@RequestMapping("/decrypt")
	@ResponseBody
	public EnDecryptResult decrypt(EncryptedData encryptedData) {
		EnDecryptResult result = new EnDecryptResult();
		try {
			result.setTaskType("decrypt");
			String type = encryptedData.getType();
			long timestamp = encryptedData.getTimestamp();
			String postedHash = encryptedData.getHash();
			String postedData = encryptedData.getData();
			String ID = encryptedData.getID();
			result.setType(type);
			result.setTimestamp(timestamp);
			result.setPostedHash(postedHash);
			result.setPostedData(postedData);
			result.setID(ID);
			if (!"data".equals(type))
				throw new Exception("Error: package type is not data.");
			if (Math.abs(timestamp - new Date().getTime()) >= Config.timeout)
				throw new Exception("Error: package timeout.");
			byte[] AESKey = Encryption.genAESKey(timestamp, ID, IMEI, credential);
			result.setAESKey(Hex.encodeHexString(AESKey));
			byte[] dataBytes = Encryption.AESDecryption(timestamp, AESKey, Encryption.decodeBase64(postedData));
			String decryptedData = new String(dataBytes, StandardCharsets.UTF_8);
			result.setDecryptedData(decryptedData);
			byte[] calculatedHash = Encryption
					.sha256(Encryption.concatArrays(dataBytes, Encryption.longToBytes(timestamp)));
			byte[] _postedHash = Encryption.decodeBase64(postedHash);
			result.setCalculatedHash(Encryption.encodeBase64(calculatedHash));
			if (!Arrays.equals(_postedHash, calculatedHash))
				throw new Exception("Error: hash value not equal!");
		} catch (Exception e) {
			// TODO Auto-generated catch block
			result.setError(e.toString());
		}
		return result;
	}

	@RequestMapping("/encrypt")
	@ResponseBody
	public EnDecryptResult encrypt(EncryptedData encryptedData) {
		EnDecryptResult result = new EnDecryptResult();
		try {
			result.setTaskType("encrypt");
			long timestamp = encryptedData.getTimestamp();
			String postedData = encryptedData.getData();
			String ID = encryptedData.getID();
			result.setTimestamp(timestamp);
			result.setPostedData(postedData);
			result.setID(ID);
			byte[] AESKey = Encryption.genAESKey(timestamp, ID, IMEI, credential);
			result.setAESKey(Hex.encodeHexString(AESKey));
			byte[] dataBytes = Encryption.decodeBase64(postedData);
			byte[] _encryptedData = Encryption.AESEncryption(timestamp, AESKey, dataBytes);
			result.setEncryptedData(Encryption.encodeBase64(_encryptedData));
			byte[] calculatedHash = Encryption
					.sha256(Encryption.concatArrays(dataBytes, Encryption.longToBytes(timestamp)));
			result.setCalculatedHash(Encryption.encodeBase64(calculatedHash));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			result.setError(e.toString());
		}
		return result;
	}

	@RequestMapping("/rsa_encrypt")
	@ResponseBody
	public EnDecryptResult rsa_encrypt(EncryptedData encryptedData) {
		EnDecryptResult result = new EnDecryptResult();
		try {
			KeyPair keyPair = Encryption.newRSAKeyPair();
			String pri = "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";
			String pub = "MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAoR2UVwzvk3Qg7tuCqPeUS1m26n3qT/uRrlmt2maSY1sZ7zhbWWumXj+aZ4geoc0EDDuiKb26Ljdn8ZCSwpeLAU3+8CqY+FYpiioi8ndcgBKSkHJXo2NtAbffkYzfJ/STEa6baHR0mZPt4Aj4ABO43nQrkpwWsnoEdkIRl5yByOGPzf+78L3dPy4+1eAMAUC6JQzca//q0wyvXxIMH7eqGlkoh5pvd5/mWpKw9CsyCPfmvz4mjkoAx2trQJCeY3YpY2TBgg1KueeRLmiJyttMRbBOwQq/Wp3qj86GLGKObuP5yLjlZ8YmplW30cxEs0QLf0Ned6a/9FVlhX3Pxn8vHFHS+Bwxn9qhsX1YAlyUyMXBPoo/+NRIQ6Op05kG64g4b3skyK2ZI1GuyHfnJEJcpWp83fdhpugQak4j+gx/CcqEJRxNUu68xVGF/zrPQOfoQqva++6xUFfgQOvqgzdUxNvjnCndbv0H5WbCEEsxWroaR8teP1B1Ya3PIIGFDUU4CCsWmTMEDitholjzytvBIqSX6CZq9OnWAzN9b0pwtx4QktN2o6AXyNTQMR18jxY0QaKEsqu/UNj3enzitrul8vWdZ8yGTekOG2cIkKdz2y60Xm2hmFdCUHexRAdYMKKx7fd4Uq0uda+LPtCXXNS+fQyP6pfyRngu8ZQ/4hbj1YcCAwEAAQ==";
//			byte[] res0 = Encryption.RSAEncryption(pub, "hello world!".getBytes(StandardCharsets.UTF_8));
//			byte[] res1 = Encryption.RSADecryption(pri, res0);
			byte[] res0 = Encryption.RSAAESEncryption(pub, pri.getBytes(StandardCharsets.UTF_8));
			String file = "/a/project/smart_lock/rsa_c/encrypted_output";
			byte[] buffer = new byte[(int) new File(file).length()];
			int len = IOUtils.read(new FileInputStream(file), buffer);
			byte[] res1 = Encryption.RSAAESDecryption(pri, buffer);
			IOUtils.write(res0, new FileOutputStream("/a/project/smart_lock/rsa_c/decrypted_output"));
//			String res2 = new String(res1, StandardCharsets.UTF_8);
//			boolean ok = res2.equals(pri);
			String temp = "res2";
//			String res2 = new String(res1, StandardCharsets.UTF_8);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			result.setError(e.toString());
		}
		return result;
	}

}
