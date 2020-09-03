/*
 * config.h
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define CREDENTIAL_LEN 1024

#define LOCK_ID "7a5d156d704d20a77477d0aae1291be7"
#define CLIENT_ID "145db89e8a4b347b4030d273c03a06ba"
#define SERVER_ADDR "http://39.107.123.167:8082/lock/"
//#define SERVER_ADDR "http://192.168.0.105:8082/lock/"
#define SERVER_GET_ADDR SERVER_ADDR "msg/get"
#define SERVER_SEND_ADDR SERVER_ADDR "msg/send"
#define SERVER_GET_MSG_ADDR SERVER_GET_ADDR "?id=" LOCK_ID

#endif /* CONFIG_H_ */
