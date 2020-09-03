/*
 * log.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef MODEL_LOG_H_
#define MODEL_LOG_H_

#include <stdint.h>
class Log {
private:
	int id;
	int creator;
	int64_t create_time;
	int type;
	char *content;
	bool is_deleted;
	char *remark;

public:
	Log();
	Log(int id, int creator, int64_t create_time, int type, char *content,
			bool is_deleted, char *remark);
	~Log();

public:
	char* getContent() const;
	void setContent(char const *content);
	int64_t getCreateTime() const;
	void setCreateTime(int64_t createTime);
	int getCreator() const;
	void setCreator(int creator);
	int getId() const;
	void setId(int id);
	bool isIsDeleted() const;
	void setIsDeleted(bool isDeleted);
	char* getRemark() const;
	void setRemark(char const *remark);
	int getType() const;
	void setType(int type);
};

#endif /* MODEL_LOG_H_ */
