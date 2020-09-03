package com.smart.lock.model;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.Cookie;

public class TestData {
	public static class Part {
		private String name;
		private HashMap<String, String> headers;
		private String contentType;
		private long size;
		private String submittedFileName;
		private String data;
		
		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;
		}
		public HashMap<String, String> getHeaders() {
			return headers;
		}
		public void setHeaders(HashMap<String, String> headers) {
			this.headers = headers;
		}
		public String getContentType() {
			return contentType;
		}
		public void setContentType(String contentType) {
			this.contentType = contentType;
		}
		public long getSize() {
			return size;
		}
		public void setSize(long size) {
			this.size = size;
		}
		public String getSubmittedFileName() {
			return submittedFileName;
		}
		public void setSubmittedFileName(String submittedFileName) {
			this.submittedFileName = submittedFileName;
		}
		public String getData() {
			return data;
		}
		public void setData(String data) {
			this.data = data;
		}
	}

	private String authType;
	private String characterEncoding;
	private Long contentLengthLong;
	private String contentType;
	private String localAddr;
	private String locale;
	private String localName;
	private int localPort;
	private String method;
	private String protocol;
	private String queryString;
	private String remoteAddr;
	private String remoteHost;
	private int remotePort;
	private String remoteUser;
	private String requestURI;
	private String scheme;
	private Cookie[] cookies;
	private HashMap<String, String> headers;
	private HashMap<String, Part> parts;
	private String error;

	private Map<String, String[]> parameterMap;

	public String getAuthType() {
		return authType;
	}

	public void setAuthType(String authType) {
		this.authType = authType;
	}

	public String getCharacterEncoding() {
		return characterEncoding;
	}

	public void setCharacterEncoding(String characterEncoding) {
		this.characterEncoding = characterEncoding;
	}

	public Long getContentLengthLong() {
		return contentLengthLong;
	}

	public void setContentLengthLong(Long contentLengthLong) {
		this.contentLengthLong = contentLengthLong;
	}

	public String getContentType() {
		return contentType;
	}

	public void setContentType(String contentType) {
		this.contentType = contentType;
	}

	public String getLocalAddr() {
		return localAddr;
	}

	public void setLocalAddr(String localAddr) {
		this.localAddr = localAddr;
	}

	public String getLocale() {
		return locale;
	}

	public void setLocale(String locale) {
		this.locale = locale;
	}

	public String getLocalName() {
		return localName;
	}

	public void setLocalName(String localName) {
		this.localName = localName;
	}

	public int getLocalPort() {
		return localPort;
	}

	public void setLocalPort(int localPort) {
		this.localPort = localPort;
	}

	public String getMethod() {
		return method;
	}

	public void setMethod(String method) {
		this.method = method;
	}

	public String getProtocol() {
		return protocol;
	}

	public void setProtocol(String protocol) {
		this.protocol = protocol;
	}

	public String getQueryString() {
		return queryString;
	}

	public void setQueryString(String queryString) {
		this.queryString = queryString;
	}

	public String getRemoteAddr() {
		return remoteAddr;
	}

	public void setRemoteAddr(String remoteAddr) {
		this.remoteAddr = remoteAddr;
	}

	public String getRemoteHost() {
		return remoteHost;
	}

	public void setRemoteHost(String remoteHost) {
		this.remoteHost = remoteHost;
	}

	public int getRemotePort() {
		return remotePort;
	}

	public void setRemotePort(int remotePort) {
		this.remotePort = remotePort;
	}

	public String getRemoteUser() {
		return remoteUser;
	}

	public void setRemoteUser(String remoteUser) {
		this.remoteUser = remoteUser;
	}

	public String getRequestURI() {
		return requestURI;
	}

	public void setRequestURI(String requestURI) {
		this.requestURI = requestURI;
	}

	public String getScheme() {
		return scheme;
	}

	public void setScheme(String scheme) {
		this.scheme = scheme;
	}

	public Map<String, String[]> getParameterMap() {
		return parameterMap;
	}

	public void setParameterMap(Map<String, String[]> parameterMap) {
		this.parameterMap = parameterMap;
	}

	public Cookie[] getCookies() {
		return cookies;
	}

	public void setCookies(Cookie[] cookies) {
		this.cookies = cookies;
	}

	public HashMap<String, String> getHeaders() {
		return headers;
	}

	public void setHeaders(HashMap<String, String> headers) {
		this.headers = headers;
	}

	public HashMap<String, Part> getParts() {
		return parts;
	}

	public void setParts(HashMap<String, Part> parts) {
		this.parts = parts;
	}

	public String getError() {
		return error;
	}

	public void setError(String error) {
		this.error = error;
	}

}
