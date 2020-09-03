/*
 * user.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include "user.h"

User::User() :
		User(-1, nullptr, nullptr, nullptr, -1, -1, -1, -1, 0, 0) {
}

User::User(int id, char *username, char *credential, char *imei,
		int64_t expiration, int creator, int64_t create_time, int64_t expire_time,
		bool is_expired, bool is_deleted) :
		id(id), username(nullptr), credential(nullptr), imei(nullptr), expiration(
				expiration), creator(creator), create_time(create_time), expire_time(
				expire_time), is_expired(is_expired), is_deleted(is_deleted) {
	if (username) {
		int len = strlen(username);
		this->username = new char[len];
		strcpy(this->username, username);
	}
	if (credential) {
		this->credential = new char[CREDENTIAL_LEN];
		strncpy(this->credential, credential, CREDENTIAL_LEN);
	}
	if (imei) {
		int len = strlen(imei);
		this->imei = new char[len];
		strcpy(this->imei, imei);
	}
}
User::~User() {
	if (!username) {
		delete[] username;
		username = nullptr;
	}
	if (!credential) {
		delete[] credential;
		credential = nullptr;
	}
	if (!imei) {
		delete[] imei;
		imei = nullptr;
	}
}

int64_t User::getCreateTime() const {
	return create_time;
}

void User::setCreateTime(int64_t createTime) {
	create_time = createTime;
}

int User::getCreator() const {
	return creator;
}

void User::setCreator(int creator) {
	this->creator = creator;
}

char* User::getCredential() const {
	return credential;
}

void User::setCredential(char const *credential) {
	if (!this->credential) {
		delete[] this->credential;
		this->credential = nullptr;
	}
	if (credential) {
		this->credential = new char[CREDENTIAL_LEN];
		strncpy(this->credential, credential, CREDENTIAL_LEN);
	}
}

int64_t User::getExpiration() const {
	return expiration;
}

void User::setExpiration(int64_t expiration) {
	this->expiration = expiration;
}

int64_t User::getExpireTime() const {
	return expire_time;
}

void User::setExpireTime(int64_t expireTime) {
	expire_time = expireTime;
}

int User::getId() const {
	return id;
}

void User::setId(int id) {
	this->id = id;
}

char* User::getImei() const {
	return imei;
}

void User::setImei(char const *imei) {
	if (!this->imei) {
		delete[] this->imei;
		this->imei = nullptr;
	}
	if (imei) {
		int len = strlen(imei);
		this->imei = new char[len];
		strcpy(this->imei, imei);
	}
}

bool User::isIsDeleted() const {
	return is_deleted;
}

void User::setIsDeleted(bool isDeleted) {
	is_deleted = isDeleted;
}

bool User::isIsExpired() const {
	return is_expired;
}

void User::setIsExpired(bool isExpired) {
	is_expired = isExpired;
}

char* User::getUsername() const {
	return username;
}

void User::setUsername(char const *username) {
	if (!this->username) {
		delete[] this->username;
		this->username = nullptr;
	}
	if (username) {
		int len = strlen(username);
		this->username = new char[len];
		strcpy(this->username, username);
	}
}
