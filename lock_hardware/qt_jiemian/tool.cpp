/*
 * tool.cpp
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#include <chrono>
#include <unistd.h>
#include "tool.h"
#include "database.h"
#include "remote_fun.h"
#include "config.h"
#include "communication.h"

std::string& dump_string_vector(std::string &json,
                                std::vector<std::string> &vec) {
	json += "[";
	for (std::vector<std::string>::iterator it = vec.begin(), end = vec.end();
	        it != end;) {
		std::string str = *it;
		json += "\"";
		ReplaceStringInPlace(str, "\\", "\\\\");
		json += ReplaceStringInPlace(str, "\"", "\\\"");
		json += "\"";
		if (end != ++it)
			json += ",";
	}
	json += "]";
	return json;
}

std::string& ReplaceStringInPlace(std::string &subject,
                                  const std::string &search, const std::string &replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}

std::string string_to_hex(const std::string &input) {
	static const char *const lut = "0123456789ABCDEF";
	size_t len = input.length();

	std::string output;
	output.reserve(2 * len);
	for (size_t i = 0; i < len; ++i) {
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}
	return output;
}

int64_t get_timestamp() {
	int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>(
	                        std::chrono::system_clock::now().time_since_epoch()).count();
	return now;
}

bool on_action_logging(log_type type, char const *title, char const *who) {
	if (!on_logging(type, title, "开锁人", who))
		return false;
	if (200 != fun::list_log())
		return false;
	usleep(300000);
	char const* notice = nullptr;
	switch (type) {
	case lock:
		notice = "新增1条关锁记录";
		break;
	case unlock:
		notice = "新增1条开锁记录";
		break;
	case open_door:
		notice = "新增1条开门记录";
		break;
	case close_door:
		notice = "新增1条关门记录";
		break;
	default:
		notice = "This is an error!";
	}
	// if (lock == type || unlock == type)
		return on_notice("log", notice, "");
}

bool on_warn_logging(log_type type, char const *title, char const *warn_type,
                     char const *warn_detail) {
	if (!on_logging(type, title, "类型", warn_type, "详细信息", warn_detail))
		return false;
	if (200 != fun::list_log())
		return false;
	usleep(300000);
	return on_notice(abnormal == type ? "abnormal" : "danger", title,
	                 warn_detail);
}

bool on_notice(char const *type, char const *title, char const *content) {
	std::string response;
	std::string str;
	rapidjson::Document data(rapidjson::kObjectType);
	int64_t status = communication::send_msg(LOCK_ID, CLIENT_ID,
	                                      communication::new_msg(str, "on_notice",
	                                              rapidjson::ToObject(data, "type", type, "title", title,
	                                                      "content", content)).c_str(), response);
	return 200 == status;
}

