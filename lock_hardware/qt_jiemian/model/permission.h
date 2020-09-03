/*
 * permission.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef MODEL_PERMISSION_H_
#define MODEL_PERMISSION_H_

#include <stdint.h>
#include "permission.h"

#include <string.h>

class Permission {
private:
	int id;
	int user;
	bool unlock;
	bool add_user;
	bool update_user;
	bool update_permission;
	bool list_log;
	bool view_status;
	bool add_password;
	bool update_password;
	bool list_password;
	bool view_monitor;
	bool megaphone;

public:
	Permission();
	Permission(int id, int user, bool unlock, bool add_user, bool update_user,
			bool update_permission, bool list_log, bool view_status,
			bool add_password, bool update_password, bool list_password,
			bool view_monitor, bool megaphone);
	~Permission();

public:
	bool isAddPassword() const;
	void setAddPassword(bool addPassword);
	bool isAddUser() const;
	void setAddUser(bool addUser);
	int getId() const;
	void setId(int id);
	bool isListLog() const;
	void setListLog(bool listLog);
	bool isListPassword() const;
	void setListPassword(bool listPassword);
	bool isMegaphone() const;
	void setMegaphone(bool megaphone);
	bool isUnlock() const;
	void setUnlock(bool unlock);
	bool isUpdatePassword() const;
	void setUpdatePassword(bool updatePassword);
	bool isUpdatePermission() const;
	void setUpdatePermission(bool updatePermission);
	bool isUpdateUser() const;
	void setUpdateUser(bool updateUser);
	int getUser() const;
	void setUser(int user);
	bool isViewMonitor() const;
	void setViewMonitor(bool viewMonitor);
	bool isViewStatus() const;
	void setViewStatus(bool viewStatus);

};

#endif /* MODEL_PERMISSION_H_ */
