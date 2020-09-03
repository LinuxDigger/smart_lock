/*
 * log.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include "log.h"
#include <string.h>

Log::Log() : Log(-1, -1, -1, -1, nullptr, 0, nullptr)
{
}
Log::Log(int id, int creator, int64_t create_time, int type, char *content,
		 bool is_deleted, char *remark) : id(id), creator(creator), create_time(create_time), type(type), content(nullptr), is_deleted(is_deleted), remark(nullptr)
{

	if (content)
	{
		int len = strlen(content);
		this->content = new char[len + 1];
		strcpy(this->content, content);
		this->content[len] = 0;
	}
	if (remark)
	{
		int len = strlen(remark);
		this->remark = new char[len + 1];
		strcpy(this->remark, remark);
		this->remark[len] = 0;
	}
}
Log::~Log()
{
	if (!content)
	{
		delete[] content;
		content = nullptr;
	}
	if (!remark)
	{
		delete[] remark;
		remark = nullptr;
	}
}

char *Log::getContent() const
{
	return content;
}

void Log::setContent(char const *content)
{
	if (!this->content)
	{
		delete[] this->content;
		this->content = nullptr;
	}
	if (content)
	{
		int len = strlen(content);
		this->content = new char[len + 1];
		strcpy(this->content, content);
		this->content[len] = 0;
	}
}

int64_t Log::getCreateTime() const
{
	return create_time;
}

void Log::setCreateTime(int64_t createTime)
{
	create_time = createTime;
}

int Log::getCreator() const
{
	return creator;
}

void Log::setCreator(int creator)
{
	this->creator = creator;
}

int Log::getId() const
{
	return id;
}

void Log::setId(int id)
{
	this->id = id;
}

bool Log::isIsDeleted() const
{
	return is_deleted;
}

void Log::setIsDeleted(bool isDeleted)
{
	is_deleted = isDeleted;
}

char *Log::getRemark() const
{
	return remark;
}

void Log::setRemark(char const *remark)
{
	if (!this->remark)
	{
		delete[] this->remark;
		this->remark = nullptr;
	}
	if (remark)
	{
		int len = strlen(remark);
		this->remark = new char[len + 1];
		strcpy(this->remark, remark);
		this->remark[len] = 0;
	}
}

int Log::getType() const
{
	return type;
}

void Log::setType(int type)
{
	this->type = type;
}
