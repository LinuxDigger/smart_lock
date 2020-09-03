/*
 * hardware.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include <sqlite3.h>
#include <iostream>
#include "hardware.h"
#include "database.h"
#include "src/server_moto/server_moto.h"
#include "tool.h"
#include "src/camera/camera.h"

namespace hw {

bool open_door() {
	OPEN_DOOR();
	std::cout << "Door opened!!!" << std::endl;
	return true;
}
bool close_door() {
	CLOSE_DOOR();
	std::cout << "Door closed!!!" << std::endl;
	return true;
}

bool lock() {
	LOCK_DOOR();
	std::cout << "locked!!!" << std::endl;
	return true;
}
bool unlock() {
	UNLOCK_DOOR();
	std::cout << "unlocked!!!" << std::endl;
	return true;
}

bool get_image(std::string &path) {
	// 获取摄像头图片保存到任意路径;
	if(take_a_picture())
		return false;
	//将图片路径赋值给path; *** 最好是绝对路径 ***
	path = "/capture.jpg";
	return true;
}

//on_warn_logging(log_type::abnormal, "异常警告", "异常人员",
//		"有未知人员在门前停留时间超过一分钟，在该期间内监测到门有轻微的震动，但是该人员并未尝试开启门锁。");


}

