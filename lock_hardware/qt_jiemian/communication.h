/*
 * communication.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

#include <stdint.h>
#include <string>
#include <thread>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "tool.h"

namespace communication {

int send_msg(char const *from, char const *to, char const *msg,
		std::string &response, bool mark_image = false);
int get_msg(char const *id, std::string &response);
std::thread* start_long_polling();

template<typename ... Args>
std::string new_msg(std::string &str, char const *type, Args &&... args) {
	rapidjson::Document document(rapidjson::kObjectType);
	rapidjson::Document::AllocatorType &allocator = document.GetAllocator();
	document.AddMember("type", rapidjson::StringRef(type), allocator);
	rapidjson::Document data(rapidjson::kArrayType);
	rapidjson::ToArray(data, args...);
	document.AddMember("data", data, allocator);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	str = buffer.GetString();
	return str;
}

}

#endif /* COMMUNICATION_H_ */
