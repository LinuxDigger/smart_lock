/*
 * remote_fun.cpp
 *
 *  Created on: Jul 16, 2020
 *      Author: davies
 */

#include <vector>
#include <fstream>
#include <iterator>
#include "remote_fun.h"
#include "database.h"
#include "logger.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "model/user.h"
#include "model/log.h"
#include "model/password.h"
#include "model/permission.h"
#include "communication.h"
#include "config.h"
#include "hardware.h"
#include "algorithm/base64.h"

namespace fun {

int list_log() {
	std::vector<Log> logs;
	if (0 >= list_log(logs)) {
		log_err("list_log(logs) error!");
		return -1;
	}
	rapidjson::Document _logs(rapidjson::kArrayType);
	rapidjson::Document::AllocatorType &allocator = _logs.GetAllocator();

	for (std::vector<Log>::iterator it = logs.begin(); it != logs.end(); ++it) {
		int id = it->getId();
		int creator = it->getCreator();
		int64_t create_time = it->getCreateTime();
		int type = it->getType();
		char *content = it->getContent();
		bool is_deleted = it->isIsDeleted();
		char *remark = it->getRemark();
		rapidjson::Value _log(rapidjson::kObjectType);
		_log.AddMember("id", id, allocator);
		_log.AddMember("creator", creator, allocator);
		_log.AddMember("create_time", (int64_t) create_time, allocator);
		_log.AddMember("type", type, allocator);
		_log.AddMember("content", rapidjson::StringRef(content), allocator);
		_log.AddMember("is_deleted", is_deleted, allocator);
		_log.AddMember("remark", rapidjson::StringRef(remark), allocator);
		_logs.PushBack(_log, allocator);
	}

	std::string response;
	std::string str;
	int64_t status = communication::send_msg(LOCK_ID, CLIENT_ID,
			communication::new_msg(str, "on_list_log", _logs).c_str(),
			response);
	return status;
}

int list_password() {
	std::vector<Password> passwords;
	if (0 >= list_password(passwords)) {
		log_err("list_log(logs) error!");
		return -1;
	}
	rapidjson::Document _passwords(rapidjson::kArrayType);
	rapidjson::Document::AllocatorType &allocator = _passwords.GetAllocator();

	for (std::vector<Password>::iterator it = passwords.begin();
			it != passwords.end(); ++it) {
		int id = it->getId();
		int64_t expiration = it->getExpiration();
		int creator = it->getCreator();
		int64_t create_time = it->getCreateTime();
		char *content = it->getContent();
		bool is_expired = it->isIsExpired();
		bool is_urgent = it->isIsUrgent();
		bool is_deleted = it->isIsDeleted();
		rapidjson::Value _password(rapidjson::kObjectType);
		_password.AddMember("id", id, allocator);
		_password.AddMember("expiration", (int64_t) expiration, allocator);
		_password.AddMember("creator", creator, allocator);
		_password.AddMember("create_time", (int64_t) create_time, allocator);
		_password.AddMember("content", rapidjson::StringRef(content),
				allocator);
		_password.AddMember("is_expired", is_expired, allocator);
		_password.AddMember("is_urgent", is_urgent, allocator);
		_password.AddMember("is_deleted", is_deleted, allocator);
		_passwords.PushBack(_password, allocator);
	}

	std::string response;
	std::string str;
	int64_t status = communication::send_msg(LOCK_ID, CLIENT_ID,
			communication::new_msg(str, "on_list_password", _passwords).c_str(),
			response);
	return status;
}

int get_image(bool mark_image) {
	std::string path;
	if (!hw::get_image(path))
		return -1;
	std::ifstream in(path.c_str());
	std::string image((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());
	std::string base64_img = base64_encode((unsigned char const*) image.c_str(),
			image.size());

	std::string response;
	std::string str;
	rapidjson::Document marked_image(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType &allocator = marked_image.GetAllocator();
	rapidjson::Value null_value;
	rapidjson::ToObject(marked_image, "info", null_value, "base64_img",
			base64_img.c_str());
	int64_t status = communication::send_msg(LOCK_ID, CLIENT_ID,
			communication::new_msg(str, "on_get_image", marked_image).c_str(),
			response, mark_image);

	return 200 == status;
}

}
