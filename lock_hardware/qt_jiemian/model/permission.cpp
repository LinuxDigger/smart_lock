/*
 * permission.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include "permission.h"

#include <string.h>

Permission::Permission() :
		Permission(-1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {
}
Permission::Permission(int id, int user, bool unlock, bool add_user,
		bool update_user, bool update_permission, bool list_log,
		bool view_status, bool add_password, bool update_password,
		bool list_password, bool view_monitor, bool megaphone) :
		id(id), user(user), unlock(unlock), add_user(add_user), update_user(
				update_user), update_permission(update_permission), list_log(
				list_log), view_status(view_status), add_password(add_password), update_password(
				update_password), list_password(list_password), view_monitor(
				view_monitor), megaphone(megaphone) {

}
Permission::~Permission() {
}

bool Permission::isAddPassword() const {
	return add_password;
}

void Permission::setAddPassword(bool addPassword) {
	add_password = addPassword;
}

bool Permission::isAddUser() const {
	return add_user;
}

void Permission::setAddUser(bool addUser) {
	add_user = addUser;
}

int Permission::getId() const {
	return id;
}

void Permission::setId(int id) {
	this->id = id;
}

bool Permission::isListLog() const {
	return list_log;
}

void Permission::setListLog(bool listLog) {
	list_log = listLog;
}

bool Permission::isListPassword() const {
	return list_password;
}

void Permission::setListPassword(bool listPassword) {
	list_password = listPassword;
}

bool Permission::isMegaphone() const {
	return megaphone;
}

void Permission::setMegaphone(bool megaphone) {
	this->megaphone = megaphone;
}

bool Permission::isUnlock() const {
	return unlock;
}

void Permission::setUnlock(bool unlock) {
	this->unlock = unlock;
}

bool Permission::isUpdatePassword() const {
	return update_password;
}

void Permission::setUpdatePassword(bool updatePassword) {
	update_password = updatePassword;
}

bool Permission::isUpdatePermission() const {
	return update_permission;
}

void Permission::setUpdatePermission(bool updatePermission) {
	update_permission = updatePermission;
}

bool Permission::isUpdateUser() const {
	return update_user;
}

void Permission::setUpdateUser(bool updateUser) {
	update_user = updateUser;
}

int Permission::getUser() const {
	return user;
}

void Permission::setUser(int user) {
	this->user = user;
}

bool Permission::isViewMonitor() const {
	return view_monitor;
}

void Permission::setViewMonitor(bool viewMonitor) {
	view_monitor = viewMonitor;
}

bool Permission::isViewStatus() const {
	return view_status;
}

void Permission::setViewStatus(bool viewStatus) {
	view_status = viewStatus;
}
