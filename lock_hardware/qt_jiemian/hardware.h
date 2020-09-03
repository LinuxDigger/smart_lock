/*
 * hardware.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef HARDWARE_H_
#define HARDWARE_H_

#include <stdint.h>
#include <string>
#include "data_type.h"

namespace hw {

bool open_door();
bool close_door();
bool lock();
bool unlock();
bool get_image(std::string & path);
bool on_logging(log_type type, char const *content, char const *remark);

}

#endif /* HARDWARE_H_ */
