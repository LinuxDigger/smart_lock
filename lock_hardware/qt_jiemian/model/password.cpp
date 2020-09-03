/*
 * password.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include "password.h"

Password::Password() :
		Password(-1, -1, -1, -1, nullptr, 0, 0, 0) {

}
Password::Password(int id, int64_t expiration, int creator, int64_t create_time,
		char const *content, bool is_expired, bool is_urgent, bool is_deleted) :
		id(id), expiration(expiration), creator(creator), create_time(
				create_time), content(nullptr), is_expired(is_expired), is_urgent(
				is_urgent), is_deleted(is_deleted) {

	if (content) {
		int len = strlen(content);
		this->content = new char[len+1];
		strcpy(this->content, content);
		this->content[len]=0;
	}

}
Password::~Password() {
	if (!content) {
		delete[] content;
		content = nullptr;
	}

}

char* Password::getContent() const {
	return content;
}

void Password::setContent(char const *content) {
	if (!this->content) {
		delete[] this->content;
		this->content = nullptr;
	}
	if (content) {
		int len = strlen(content);
		this->content = new char[len+1];
		strcpy(this->content, content);
		this->content[len]=0;
	}
}

int64_t Password::getCreateTime() const {
	return create_time;
}

void Password::setCreateTime(int64_t createTime) {
	create_time = createTime;
}

int Password::getCreator() const {
	return creator;
}

void Password::setCreator(int creator) {
	this->creator = creator;
}

int64_t Password::getExpiration() const {
	return expiration;
}

void Password::setExpiration(int64_t expiration) {
	this->expiration = expiration;
}

int Password::getId() const {
	return id;
}

void Password::setId(int id) {
	this->id = id;
}

bool Password::isIsDeleted() const {
	return is_deleted;
}

void Password::setIsDeleted(bool isDeleted) {
	is_deleted = isDeleted;
}

bool Password::isIsExpired() const {
	return is_expired;
}

void Password::setIsExpired(bool isExpired) {
	is_expired = isExpired;
}

bool Password::isIsUrgent() const {
	return is_urgent;
}

void Password::setIsUrgent(bool isUrgent) {
	is_urgent = isUrgent;
}
