/*
 * password.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef MODEL_PASSWORD_H_
#define MODEL_PASSWORD_H_

#include <stdint.h>
#include <string.h>

class Password {
private:
	int id;
	int64_t expiration;
	int creator;
	int64_t create_time;
	char *content;
	bool is_expired;
	bool is_urgent;
	bool is_deleted;

public:
	Password();
	Password(int id, int64_t expiration, int creator, int64_t create_time,
			char const *content, bool is_expired, bool is_urgent,
			bool is_deleted);
	~Password();

public:

	char* getContent() const;
	void setContent(char const *content);
	int64_t getCreateTime() const;
	void setCreateTime(int64_t createTime);
	int getCreator() const;
	void setCreator(int creator);
	int64_t getExpiration() const;
	void setExpiration(int64_t expiration);
	int getId() const;
	void setId(int id);
	bool isIsDeleted() const;
	void setIsDeleted(bool isDeleted);
	bool isIsExpired() const;
	void setIsExpired(bool isExpired);
	bool isIsUrgent() const;
	void setIsUrgent(bool isUrgent);

};

#endif /* MODEL_PASSWORD_H_ */
