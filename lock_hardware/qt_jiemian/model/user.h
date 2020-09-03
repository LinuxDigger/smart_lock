/*
 * user.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef MODEL_USER_H_
#define MODEL_USER_H_

#include <stdint.h>
#include <string>
#include <string.h>
#include "../config.h"

class User {
private:
	int id;
	char *username;
	char *credential;
	char *imei;
	int64_t expiration;
	int creator;
	int64_t create_time;
	int64_t expire_time;
	bool is_expired;
	bool is_deleted;

public:
	User();
	User(int id, char *username, char *credential, char *imei, int64_t expiration,
			int creator, int64_t create_time, int64_t expire_time, bool is_expired,
			bool is_deleted);
	~User();

public:
	int64_t getCreateTime() const;
	void setCreateTime(int64_t createTime);
	int getCreator() const;
	void setCreator(int creator);
	char* getCredential() const;
	void setCredential(char const *credential);
	int64_t getExpiration() const;
	void setExpiration(int64_t expiration);
	int64_t getExpireTime() const;
	void setExpireTime(int64_t expireTime);
	int getId() const;
	void setId(int id);
	char* getImei() const;
	void setImei(char const *imei);
	bool isIsDeleted() const;
	void setIsDeleted(bool isDeleted);
	bool isIsExpired() const;
	void setIsExpired(bool isExpired);
	char* getUsername() const;
	void setUsername(char const *username);

};

#endif /* MODEL_USER_H_ */
