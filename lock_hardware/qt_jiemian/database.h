/*
 * database.h
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#ifndef DATABASE_H_
#define DATABASE_H_

#include <stdint.h>
#include <iostream>
#include <sqlite3.h>
#include "data_type.h"

class User;
class Log;
class Password;
class Permission;

bool database_init(sqlite3 *db);

int query_callback(void *data, int argc, char **argv, char **azColName);

int query(sqlite3 *db, QueryResult *query_result, char const *sql);

int add_user(char const *username, char const *credential, char const *imei,
		int64_t expiration, int64_t creator, int64_t create_time, int64_t expire_time,
		bool is_expired, bool is_deleted);
int get_last_insert_rowid(sqlite3 *db);
int get_user(int _id, User &user);
int update_user(User const &user);
int list_user(std::vector<User> &users);

int add_log(int creator, int64_t create_time, int type, char const *content,
		bool is_deleted, char const *remark);
int list_log(std::vector<Log> &logs);

int add_password(int64_t expiration, int creator, int64_t create_time,
		char const *content, bool is_expired, bool is_urgent, bool is_deleted);
int get_password(int _id, Password &password);
int update_password(Password const &password);
int list_password(std::vector<Password> &passwords);
int add_permission(int user, bool unlock, bool add_user, bool update_user,
		bool update_permission, bool list_log, bool view_status,
		bool add_password, bool update_password, bool list_password,
		bool view_monitor, bool megaphone);
int get_permission(int _id, Permission &permission);
int update_permission(Permission const &permission);
int list_permission(std::vector<Permission> &permissions);

#endif /* DATABASE_H_ */
