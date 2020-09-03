/*
 * data_type.h
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#ifndef DATA_TYPE_H_
#define DATA_TYPE_H_

#include <stdint.h>
#include <vector>
#include <string>

class QueryResult {
private:
	int has_error;
	int col_count;
	int record_count;
	std::string error_msg;
	std::vector<std::string> header;
	std::vector<std::vector<std::string>> records;
public:
	int has_set_header;

public:
	QueryResult();
	~QueryResult();
	void set_header(int argc, char **azColName);
	void set_record(char **argv);
	std::vector<std::string>& get_header();
	std::vector<std::vector<std::string>>& get_records();
	std::string& get_error_msg();
	void set_error_msg(std::string const &error_msg);
	bool has_error_();
	void has_error_(int has_error);
	bool col_count_();
	bool record_count_();
	std::string& dump_json(std::string &json);
};


enum log_type {
	lock, unlock, open_door, close_door,abnormal,danger, info, error
};

#endif /* DATA_TYPE_H_ */
