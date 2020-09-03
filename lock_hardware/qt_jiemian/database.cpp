#include <string.h>
#include "database.h"
#include "tool.h"
#include "config.h"
#include "model/user.h"
#include "model/log.h"
#include "model/password.h"
#include "model/permission.h"

sqlite3 *database_db;

bool database_init(sqlite3 *db) {
	database_db = db;
	return true;
}

int query_callback(void *data, int argc, char **argv, char **azColName) {
	QueryResult *query_result = (QueryResult*) data;
	if (!query_result->has_set_header)
		query_result->set_header(argc, azColName);

	query_result->set_record(argv);
	std::string json;
	return 0;
}

int query(sqlite3 *db, QueryResult *query_result, char const *sql) {
	char *zErrMsg = NULL;
	if (SQLITE_OK
			!= sqlite3_exec(db, sql, query_callback, query_result, &zErrMsg)) {
		query_result->has_error_(1);
		query_result->set_error_msg(zErrMsg);
		return 0;
	}
	return 1;
}

int get_last_insert_rowid() {
	const char *sql = "SELECT last_insert_rowid();";
	sqlite3_stmt *statement;
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}
	if (SQLITE_ROW != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -1;
	}
	int id = sqlite3_column_int(statement, 0);
	sqlite3_finalize(statement);
	return id;
}

int add_user(char const *username, char const *credential, char const *imei,
		int64_t expiration, int64_t creator, int64_t create_time, int64_t expire_time,
		bool is_expired, bool is_deleted) {

	sqlite3_stmt *statement;
	const char *sql =
			"INSERT INTO user (username,credential,imei,expiration,creator,create_time,expire_time,is_expired,is_deleted) VALUES (?,?,?,?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_text(statement, 1, username, strlen(username),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_blob(statement, 2, credential, CREDENTIAL_LEN,
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 3, imei, strlen(imei),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 4, expiration) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 5, creator) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int64(statement, 6, create_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 7, expire_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 8, is_expired) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 9, is_deleted) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (SQLITE_DONE != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -2;
	}
	sqlite3_finalize(statement);
	return get_last_insert_rowid();

//	while (true) {
//		if (SQLITE_ROW == sqlite3_step(statement)) {
//			int id = sqlite3_column_int(statement, 0);
//			ids.push_back(id);
//
//			int size = sqlite3_column_bytes(statement, 1);
//			std::vector<byte> data((byte) sqlite3_column_blob(statement, 1),
//					size);
//			images.push_back(cv::imdecode(data, CV_LOAD_IMAGE_COLOR));
//
//			char *name = (char*) sqlite3_column_text(statement, 2);
//			names.push_back(name);
//		} else {
//			break;
//		}
//	}

//	std::string sql;
//	std::string temp;
//	ReplaceStringInPlace(temp = username, "'", "''");
//	sql = string_format("", ReplaceStringInPlace(temp = username, "'", "''"),
//			string_to_hex(credential), imei, expiration, creator, create_time,
//			expire_time, is_expired, is_deleted);
//
//	QueryResult query_result;
//	return query(database_db, &query_result, "");
}

int get_user(int _id, User &user) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,username,credential,imei,expiration,creator,create_time,expire_time,is_expired,is_deleted FROM user WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	if (sqlite3_bind_int(statement, 1, _id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -1;
	}

	if (SQLITE_ROW != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -1;
	}
	int id = sqlite3_column_int(statement, 0);
	user.setId(id);
	char const *username = (char const*) sqlite3_column_text(statement, 1);
	user.setUsername(username);
	char const *credential = (char const*) sqlite3_column_blob(statement, 2);
	user.setCredential(credential);
	char const *imei = (char const*) sqlite3_column_text(statement, 3);
	user.setImei(imei);
	int64_t expiration = sqlite3_column_int64(statement, 4);
	user.setExpiration(expiration);
	int64_t creator = sqlite3_column_int(statement, 5);
	user.setCreator(creator);
	int64_t create_time = sqlite3_column_int64(statement, 6);
	user.setCreateTime(create_time);
	int64_t expire_time = sqlite3_column_int64(statement, 7);
	user.setExpireTime(expire_time);
	bool is_expired = sqlite3_column_int(statement, 8);
	user.setIsExpired(is_expired);
	bool is_deleted = sqlite3_column_int(statement, 9);
	user.setIsDeleted(is_deleted);
	sqlite3_finalize(statement);
	return 1;
}

int update_user(User const &user) {

	sqlite3_stmt *statement;
	const char *sql =
			"UPDATE user SET username=?,credential=?,imei=?,expiration=?,creator=?,create_time=?,expire_time=?,is_expired=?,is_deleted=? WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}
	int id = user.getId();
	char const *username = user.getUsername();
	char const *credential = user.getCredential();
	char const *imei = user.getImei();
	int64_t expiration = user.getExpiration();
	int64_t creator = user.getCreator();
	int64_t create_time = user.getCreateTime();
	int64_t expire_time = user.getExpireTime();
	bool is_expired = user.isIsExpired();
	bool is_deleted = user.isIsDeleted();

	if (sqlite3_bind_text(statement, 1, username, strlen(username),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_blob(statement, 2, credential, CREDENTIAL_LEN,
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 3, imei, strlen(imei),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 4, expiration) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 5, creator) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int64(statement, 6, create_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 7, expire_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 8, is_expired) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 9, is_deleted) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}

	if (sqlite3_bind_int(statement, 10, id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (SQLITE_DONE != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -2;
	}

	sqlite3_finalize(statement);
	return 1;
}

int list_user(std::vector<User> &users) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,username,credential,imei,expiration,creator,create_time,expire_time,is_expired,is_deleted FROM user";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	while (SQLITE_ROW == sqlite3_step(statement)) {
		User user;
		int id = sqlite3_column_int(statement, 0);
		user.setId(id);
		char const *username = (char const*) sqlite3_column_text(statement, 1);
		user.setUsername(username);
		char const *credential = (char const*) sqlite3_column_blob(statement,
				2);
		user.setCredential(credential);
		char const *imei = (char const*) sqlite3_column_text(statement, 3);
		user.setImei(imei);
		int64_t expiration = sqlite3_column_int64(statement, 4);
		user.setExpiration(expiration);
		int64_t creator = sqlite3_column_int(statement, 5);
		user.setCreator(creator);
		int64_t create_time = sqlite3_column_int64(statement, 6);
		user.setCreateTime(create_time);
		int64_t expire_time = sqlite3_column_int64(statement, 7);
		user.setExpireTime(expire_time);
		bool is_expired = sqlite3_column_int(statement, 8);
		user.setIsExpired(is_expired);
		bool is_deleted = sqlite3_column_int(statement, 9);
		user.setIsDeleted(is_deleted);
		users.push_back(user);
	}
	sqlite3_finalize(statement);
	return 1;
}

int add_log(int creator, int64_t create_time, int type, char const *content,
		bool is_deleted, char const *remark) {

	sqlite3_stmt *statement;
	const char *sql =
			"INSERT INTO log (creator,create_time,type,content,is_deleted,remark) VALUES (?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int(statement, 1, creator) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 2, create_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 3, type) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 4, content, strlen(content),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 5, is_deleted) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 6, remark, strlen(remark),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}

	if (SQLITE_DONE != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -2;
	}
	sqlite3_finalize(statement);
	return get_last_insert_rowid();
}

int list_log(std::vector<Log> &logs) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,creator,create_time,type,content,is_deleted,remark FROM log;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	while (SQLITE_ROW == sqlite3_step(statement)) {
		Log log;
		int id = sqlite3_column_int(statement, 0);
		log.setId(id);
		int creator = sqlite3_column_int(statement, 1);
		log.setCreator(creator);
		int64_t create_time = sqlite3_column_int64(statement, 2);
		log.setCreateTime(create_time);
		int type = sqlite3_column_int(statement, 3);
		log.setType(type);
		char const *content = (char const*) sqlite3_column_text(statement, 4);
		log.setContent(content);
		bool is_deleted = sqlite3_column_int(statement, 5);
		log.setIsDeleted(is_deleted);
		char const *remark = (char const*) sqlite3_column_text(statement, 6);
		log.setRemark(remark);
		logs.push_back(log);
	}
	sqlite3_finalize(statement);
	return 1;
}

int add_password(int64_t expiration, int creator, int64_t create_time,
		char const *content, bool is_expired, bool is_urgent, bool is_deleted) {

	sqlite3_stmt *statement;
	const char *sql =
			"INSERT INTO password (expiration,creator,create_time,content,is_expired,is_urgent,is_deleted) VALUES (?,?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int64(statement, 1, expiration) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 2, creator) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int64(statement, 3, create_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 4, content, strlen(content),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 5, is_expired) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 6, is_urgent) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 7, is_deleted) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (SQLITE_DONE != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -2;
	}
	sqlite3_finalize(statement);
	return get_last_insert_rowid();

}

int get_password(int _id, Password &password) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,expiration,creator,create_time,content,is_expired,is_urgent,is_deleted FROM password WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	if (sqlite3_bind_int(statement, 1, _id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -1;
	}

	int id = sqlite3_column_int(statement, 0);
	password.setId(id);
	int64_t expiration = sqlite3_column_int64(statement, 1);
	password.setExpiration(expiration);
	int creator = sqlite3_column_int(statement, 2);
	password.setCreator(creator);
	int64_t create_time = sqlite3_column_int64(statement, 3);
	password.setCreateTime(create_time);
	char const *content = (char const*) sqlite3_column_text(statement, 4);
	password.setContent(content);
	bool is_expired = sqlite3_column_int(statement, 5);
	password.setIsExpired(is_expired);
	bool is_urgent = sqlite3_column_int(statement, 6);
	password.setIsUrgent(is_urgent);
	bool is_deleted = sqlite3_column_int(statement, 7);
	password.setIsDeleted(is_deleted);

	if (SQLITE_ROW != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -1;
	}
	sqlite3_finalize(statement);
	return 1;
}

int update_password(Password const &password) {

	sqlite3_stmt *statement;
	const char *sql =
			"UPDATE password SET expiration=?,creator=?,create_time=?,content=?,is_expired=?,is_urgent=?,is_deleted=? WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}
	int id = password.getId();
	int64_t expiration = password.getExpiration();
	int creator = password.getCreator();
	int64_t create_time = password.getCreateTime();
	char *content = password.getContent();
	bool is_expired = password.isIsExpired();
	bool is_urgent = password.isIsUrgent();
	bool is_deleted = password.isIsDeleted();

	if (sqlite3_bind_int64(statement, 1, expiration) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int64(statement, 2, creator) != SQLITE_OK) {
		return -2;
	}
	if (sqlite3_bind_int64(statement, 3, create_time) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_text(statement, 4, content, strlen(content),
	SQLITE_STATIC) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 5, is_expired) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 6, is_urgent) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 7, is_deleted) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 8, id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}

	sqlite3_finalize(statement);
	return 1;
}

int list_password(std::vector<Password> &passwords) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,expiration,creator,create_time,content,is_expired,is_urgent,is_deleted FROM password";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	while (SQLITE_ROW == sqlite3_step(statement)) {
		Password password;
		int id = sqlite3_column_int(statement, 0);
		password.setId(id);
		int64_t expiration = sqlite3_column_int64(statement, 1);
		password.setExpiration(expiration);
		int creator = sqlite3_column_int(statement, 2);
		password.setCreator(creator);
		int64_t create_time = sqlite3_column_int64(statement, 3);
		password.setCreateTime(create_time);
		char const *content = (char const*) sqlite3_column_text(statement, 4);
		password.setContent(content);
		bool is_expired = sqlite3_column_int(statement, 5);
		password.setIsExpired(is_expired);
		bool is_urgent = sqlite3_column_int(statement, 6);
		password.setIsUrgent(is_urgent);
		bool is_deleted = sqlite3_column_int(statement, 7);
		password.setIsDeleted(is_deleted);
		passwords.push_back(password);
	}
	sqlite3_finalize(statement);
	return 1;
}

int add_permission(int user, bool unlock, bool add_user, bool update_user,
		bool update_permission, bool list_log, bool view_status,
		bool add_password, bool update_password, bool list_password,
		bool view_monitor, bool megaphone) {

	sqlite3_stmt *statement;
	const char *sql =
			"INSERT INTO permission (user,unlock,add_user,update_user,update_permission,list_log,view_status,add_password,update_password,list_password,view_monitor,megaphone) VALUES (?,?,?,?,?,?,?,?,?,?,?,?);";

	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -2;
	}

	if (sqlite3_bind_int(statement, 1, user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 2, unlock) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 3, add_user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 4, update_user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 5, update_permission) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 6, list_log) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 7, view_status) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 8, add_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 9, update_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 10, list_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 11, view_monitor) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 12, megaphone) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}

	if (SQLITE_DONE != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -2;
	}
	sqlite3_finalize(statement);
	return get_last_insert_rowid();

}

int get_permission(int _id, Permission &permission) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT user,unlock,add_user,update_user,update_permission,list_log,view_status,add_password,update_password,list_password,view_monitor,megaphone FROM permission WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	if (sqlite3_bind_int(statement, 1, _id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -1;
	}
	int id = sqlite3_column_int(statement, 0);
	permission.setId(id);
	int user = sqlite3_column_int(statement, 1);
	permission.setUser(user);
	bool unlock = sqlite3_column_int(statement, 2);
	permission.setUnlock(unlock);
	bool add_user = sqlite3_column_int(statement, 3);
	permission.setAddUser(add_user);
	bool update_user = sqlite3_column_int(statement, 4);
	permission.setUpdateUser(update_user);
	bool update_permission = sqlite3_column_int(statement, 5);
	permission.setUpdatePermission(update_permission);
	bool list_log = sqlite3_column_int(statement, 6);
	permission.setListLog(list_log);
	bool view_status = sqlite3_column_int(statement, 7);
	permission.setViewStatus(view_status);
	bool add_password = sqlite3_column_int(statement, 8);
	permission.setAddPassword(add_password);
	bool update_password = sqlite3_column_int(statement, 9);
	permission.setUpdatePassword(update_password);
	bool list_password = sqlite3_column_int(statement, 10);
	permission.setListPassword(list_password);
	bool view_monitor = sqlite3_column_int(statement, 11);
	permission.setViewMonitor(view_monitor);
	bool megaphone = sqlite3_column_int(statement, 12);
	permission.setMegaphone(megaphone);

	if (SQLITE_ROW != sqlite3_step(statement)) {
		sqlite3_finalize(statement);
		return -1;
	}

	sqlite3_finalize(statement);
	return 1;
}

int update_permission(Permission const &permission) {

	sqlite3_stmt *statement;
	const char *sql =
			"UPDATE permission SET user=?,unlock=?,add_user=?,update_user=?,update_permission=?,list_log=?,view_status=?,add_password=?,update_password=?,list_password=?,view_monitor=?,megaphone=? WHERE id=?;";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}
	int id = permission.getId();
	int user = permission.getUser();
	bool unlock = permission.isUnlock();
	bool add_user = permission.isAddUser();
	bool update_user = permission.isUpdateUser();
	bool update_permission = permission.isUpdatePermission();
	bool list_log = permission.isListLog();
	bool view_status = permission.isViewStatus();
	bool add_password = permission.isAddPassword();
	bool update_password = permission.isUpdatePassword();
	bool list_password = permission.isListPassword();
	bool view_monitor = permission.isViewMonitor();
	bool megaphone = permission.isMegaphone();

	if (sqlite3_bind_int(statement, 1, user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 2, unlock) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 3, add_user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 4, update_user) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 5, update_permission) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 6, list_log) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 7, view_status) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 8, add_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 9, update_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 10, list_password) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 11, view_monitor) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 12, megaphone) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}
	if (sqlite3_bind_int(statement, 13, id) != SQLITE_OK) {
		sqlite3_finalize(statement);
		return -2;
	}

	sqlite3_finalize(statement);
	return 1;
}

int list_permission(std::vector<Permission> &permissions) {

	sqlite3_stmt *statement;
	const char *sql =
			"SELECT id,user,unlock,add_user,update_user,update_permission,list_log,view_status,add_password,update_password,list_password,view_monitor,megaphone FROM permission";
	if (sqlite3_prepare_v2(database_db, sql, strlen(sql), &statement,
			nullptr) != SQLITE_OK) {
		return -1;
	}

	while (SQLITE_ROW == sqlite3_step(statement)) {
		Permission permission;
		int id = sqlite3_column_int(statement, 0);
		permission.setId(id);
		int user = sqlite3_column_int(statement, 1);
		permission.setUser(user);
		bool unlock = sqlite3_column_int(statement, 2);
		permission.setUnlock(unlock);
		bool add_user = sqlite3_column_int(statement, 3);
		permission.setAddUser(add_user);
		bool update_user = sqlite3_column_int(statement, 4);
		permission.setUpdateUser(update_user);
		bool update_permission = sqlite3_column_int(statement, 5);
		permission.setUpdatePermission(update_permission);
		bool list_log = sqlite3_column_int(statement, 6);
		permission.setListLog(list_log);
		bool view_status = sqlite3_column_int(statement, 7);
		permission.setViewStatus(view_status);
		bool add_password = sqlite3_column_int(statement, 8);
		permission.setAddPassword(add_password);
		bool update_password = sqlite3_column_int(statement, 9);
		permission.setUpdatePassword(update_password);
		bool list_password = sqlite3_column_int(statement, 10);
		permission.setListPassword(list_password);
		bool view_monitor = sqlite3_column_int(statement, 11);
		permission.setViewMonitor(view_monitor);
		bool megaphone = sqlite3_column_int(statement, 12);
		permission.setMegaphone(megaphone);
		permissions.push_back(permission);
	}
	sqlite3_finalize(statement);
	return 1;
}
