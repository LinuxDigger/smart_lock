/*
 * data_type.cpp
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#include "data_type.h"
#include "tool.h"

QueryResult::QueryResult() :
		has_error(0), has_set_header(0), record_count(0), col_count(0) {
}
QueryResult::~QueryResult() {
}

void QueryResult::set_header(int argc, char **azColName) {
	col_count = argc;
	for (int i = 0; i < col_count; ++i)
		header.push_back(azColName[i]);
	has_set_header = 1;
}
void QueryResult::set_record(char **argv) {
	std::vector<std::string> _record;
	records.push_back(_record);
	std::vector<std::string> &record = records.back();
	for (int i = 0; i < col_count; ++i) {
		record.push_back(argv[i] ? argv[i] : "");
	}
	++record_count;
}

std::vector<std::string>& QueryResult::get_header() {
	return header;
}
std::vector<std::vector<std::string>>& QueryResult::get_records() {
	return records;
}
std::string& QueryResult::get_error_msg() {
	return error_msg;
}
void QueryResult::set_error_msg(std::string const &error_msg) {
	this->error_msg = error_msg;
}
bool QueryResult::has_error_() {
	return has_error;
}
void QueryResult::has_error_(int has_error) {
	this->has_error = has_error;
}
bool QueryResult::col_count_() {
	return col_count;
}
bool QueryResult::record_count_() {
	return record_count;
}

std::string& QueryResult::dump_json(std::string &json) {
	json += "[";
	dump_string_vector(json, header);

	for (std::vector<std::vector<std::string>>::iterator it = records.begin(),
			end = records.end(); it != end; ++it) {
		json += ",";
		dump_string_vector(json, *it);
	}
	json += "]";
	return json;
}



