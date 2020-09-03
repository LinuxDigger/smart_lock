/*
 * communication.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include <curl/curl.h>
#include <thread>
#include "network.h"
#include "communication.h"
#include "config.h"
#include "logger.h"
#include "rapidjson/document.h"
#include "hardware.h"
#include "remote_fun.h"
#include "tool.h"
#include "data_type.h"

namespace communication {

int send_msg(char const *from, char const *to, char const *msg,
		std::string &response, bool mark_image) {

	rapidjson::Document document(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
	document.AddMember("from", rapidjson::StringRef(from), allocator);
	rapidjson::Value _to(rapidjson::kArrayType);
	_to.PushBack(rapidjson::StringRef(to), allocator);
	document.AddMember("to", _to, allocator);
	document.AddMember("msg", rapidjson::StringRef(msg), allocator);
	if (mark_image)
		document.AddMember("mark_image", true, allocator);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	struct curl_slist *hs = nullptr;
	hs = curl_slist_append(hs, "Content-Type: application/json");
	int64_t status = network::ajax(SERVER_SEND_ADDR, buffer.GetString(), hs,
			response);
	return status;
}

int get_msg(char const *id, std::string &response) {
	int64_t status = network::ajax(SERVER_GET_MSG_ADDR, nullptr, nullptr,
			response);
	return status;
}

int on_msg(char const *from, char const *_msg) {
//	log_info(" #from: ", from, " #msg: ", _msg);
	rapidjson::Document msg;
	rapidjson::ParseResult ok = msg.Parse(_msg);
	if (ok.IsError() || !msg.IsObject()) {
		log_err("msg parse error!");
		return -1;
	}
	if (!msg.HasMember("type") || !msg.HasMember("data")) {
		log_err("msg JSON format error!");
		return -1;
	}
	if (!msg["type"].IsString() || !msg["data"].IsArray()) {
		log_err("msg JSON format error!");
		return -1;
	}
	char const *type = msg["type"].GetString();
	rapidjson::Value data = msg["data"].GetArray();
	if (!strcmp(type, "lock")) {
		hw::lock();
		on_action_logging(log_type::lock, "远程关锁", "我");
	} else if (!strcmp(type, "unlock")) {
		hw::unlock();
		on_action_logging(log_type::unlock, "远程开锁", "我");
	} else if (!strcmp(type, "open_door")) {
		hw::open_door();
		on_action_logging(log_type::open_door, "远程开门", "我");
	} else if (!strcmp(type, "close_door")) {
		hw::close_door();
		on_action_logging(log_type::close_door, "远程关门", "我");
	} else if (!strcmp(type, "list_log")) {
		fun::list_log();
	} else if (!strcmp(type, "list_password")) {
		fun::list_password();
	} else if (!strcmp(type, "get_image")) {
		fun::get_image(data[0].GetBool());
	} else {
		log_err("Unknown msg ", " #from: ", from, " #msg: ", _msg);
	}
	return 1;
}

std::thread* start_long_polling() {
	auto poll_task = []() -> int {
		log_info("poll_task start!");
		int error_count = 0;
		while (error_count <= 5) {
			std::string response;
			if (200 != get_msg(nullptr, response)) {
				++error_count;
				continue;
			}
			rapidjson::Document data;
			rapidjson::ParseResult ok = data.Parse(response.c_str());
			if (ok.IsError() || !data.IsObject()) {
				log_err("data parse error!");
				++error_count;
				continue;
			}
			if (!data.HasMember("status") || !data.HasMember("from")
					|| !data.HasMember("msg")) {
				log_err("data JSON format error!");
				++error_count;
				continue;
			}
			if (!data["status"].IsInt()
					|| (!data["from"].IsNull() && !data["from"].IsString())
					|| (!data["msg"].IsNull() && !data["msg"].IsString())) {
				log_err("data JSON data type error!");
				++error_count;
				continue;
			}
			int status = data["status"].GetInt();
			switch (status) {
			case 0:
				on_msg(data["from"].GetString(), data["msg"].GetString());
				break;
			case 1:
				break;
			default:
				break;
			}
			error_count = 0;
		}
		log_err("Tow many error attempt. Stop polling!");
		return 0;
	};
	std::thread *task = new std::thread(poll_task);
	return task;
}

}

