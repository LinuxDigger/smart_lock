/*
 * tool.h
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#ifndef TOOL_H_
#define TOOL_H_

#include <stdint.h>
#include <memory>
#include <string>
#include <stdexcept>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "data_type.h"
#include "database.h"

std::string& dump_string_vector(std::string &json,
		std::vector<std::string> &vec);
std::string& ReplaceStringInPlace(std::string &subject,
		const std::string &search, const std::string &replace);
std::string string_to_hex(const std::string &input);

int64_t get_timestamp();

template<typename ... Args>
std::string string_format(const std::string &format, Args ... args) {
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	if (size <= 0) {
		throw std::runtime_error("Error during formatting.");
	}
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

namespace rapidjson {

inline rapidjson::Document& ToArray(rapidjson::Document &d) {
	return d;
}
template<typename ... Args>
inline rapidjson::Document& ToArray(rapidjson::Document &d, char const *e,
		Args &&... args) {
	rapidjson::Value v(rapidjson::StringRef(e), d.GetAllocator());
	d.PushBack(v, d.GetAllocator());
	return ToArray(d, args...);
}
template<typename ... Args>
inline rapidjson::Document& ToArray(rapidjson::Document &d,
		rapidjson::Document &e, Args &&... args) {
	rapidjson::Value v(e, d.GetAllocator());
	d.PushBack(v, d.GetAllocator());
	return ToArray(d, args...);
}
template<class T, typename ... Args>
inline rapidjson::Document& ToArray(rapidjson::Document &d, T &&e,
		Args &&... args) {
	rapidjson::Value v(e);
	d.PushBack(v, d.GetAllocator());
	return ToArray(d, args...);
}

inline rapidjson::Document& ToObject(rapidjson::Document &d) {
	return d;
}
template<typename ... Args>
inline rapidjson::Document& ToObject(rapidjson::Document &d, char const *n,
		char const *v, Args &&... args) {
	rapidjson::Value _v(rapidjson::StringRef(v), d.GetAllocator());
	d.AddMember(rapidjson::StringRef(n), _v, d.GetAllocator());
	return ToObject(d, args...);
}
template<typename ... Args>
inline rapidjson::Document& ToObject(rapidjson::Document &d, char const *n,
		rapidjson::Document &v, Args &&... args) {
	rapidjson::Value _v(v, d.GetAllocator());
	d.AddMember(rapidjson::StringRef(n), _v, d.GetAllocator());
	return ToObject(d, args...);
}
template<typename ... Args>
inline rapidjson::Document& ToObject(rapidjson::Document &d, char const *n,
		rapidjson::Value& v, Args &&... args) {
	rapidjson::Value _v(v, d.GetAllocator());
	d.AddMember(rapidjson::StringRef(n), _v, d.GetAllocator());
	return ToObject(d, args...);
}
template<class T, typename ... Args>
inline rapidjson::Document& ToObject(rapidjson::Document &d, char const *n,
		T &&v, Args &&... args) {
	rapidjson::Value _v(v);
	d.AddMember(rapidjson::StringRef(n), _v, d.GetAllocator());
	return ToObject(d, args...);
}

}

template<typename ... Args>
bool on_logging(log_type type, char const *content, Args &&... args) {
	rapidjson::Document _remark(rapidjson::kObjectType);
	rapidjson::ToObject(_remark, args...);
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	_remark.Accept(writer);
	return 0 < add_log(0, get_timestamp(), type, content, 0, buffer.GetString());
}

bool on_action_logging(log_type type, char const *title, char const *who);
bool on_warn_logging(log_type type, char const *title, char const *warn_type,
		char const *warn_detail);
bool on_notice(char const *type, char const *title, char const *content);

#endif /* TOOL_H_ */
