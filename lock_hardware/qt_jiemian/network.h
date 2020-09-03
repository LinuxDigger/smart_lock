/*
 * network.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include <stdint.h>
#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>

namespace network {

bool inti();
int64_t ajax(char const *url, char const *body, struct curl_slist *hs,
		std::string &response);
bool uninit();

}

#endif /* NETWORK_H_ */
