

#include <stdint.h>
#include <stdio.h>
#include <iostream>

#include <unistd.h>
#include <curl/curl.h>
#include <thread>

#include "lock.h"
#include "database.h"
#include "model/user.h"
#include "model/log.h"
#include "model/password.h"
#include "model/permission.h"
#include "communication.h"
#include "network.h"
#include "lock.h"
#include "logger.h"
extern "C" {
#include "rsa_aes.h"
}

int lock_main(void) {
	sqlite3 *db;
	if (SQLITE_OK != sqlite3_open("lock.db", &db)) {
		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}

	network::inti();
	database_init(db);
	std::thread *polling = communication::start_long_polling();

//	std::string response;
//	std::string str;
//	int64_t status = communication::send_msg(LOCK_ID, CLIENT_ID,
//			communication::new_msg(str, "这个是类型", "nihao", "googogo", "24343",
//					123, true).c_str(), response);
//	std::cout << response;

//    EVP_PKEY *pubkey = EVP_PKEY_new();
//    EVP_PKEY *prikey = EVP_PKEY_new();
//
//    if (!get_rsa_pub_key("publicKey.pem", pubkey)) return -1;
//    if (!get_rsa_pri_key("privateKey.pem", prikey)) return -1;
//
//    FILE *fp = fopen("lock.cpp", "rb");
//    fseek(fp, 0L, SEEK_END);
//    unsigned sz = ftell(fp);
//    fseek(fp, 0L, SEEK_SET);
//    unsigned char *data = (unsigned char*) malloc(sz);
//    fread(data, 1, sz, fp);
//
//    int seal_out_size = get_evp_seal_out_size(sz);
//    unsigned int unseal_out_size = get_evp_unseal_safe_out_size(seal_out_size);
//    unsigned char *seal_out = (unsigned char*) malloc(seal_out_size);
//    unsigned char *unseal_out = (unsigned char*) malloc(unseal_out_size);
//
//    //进行加密
//    //输入原始数据data，和公匙pubkey，得到加密结果seal_out
//    do_evp_seal(pubkey, data, sz, seal_out);
//    //进行解密
//    //输入加密数据seal_out，和私匙prikey，得到解密结果unseal_out和解密结果长度unseal_out_size
//    do_evp_unseal(prikey, seal_out, seal_out_size, unseal_out, &unseal_out_size);
//
//    //将解密结果输出到命令行
//    fwrite(unseal_out, 1, unseal_out_size, stdout);
//
//    //将解密结果输出到文件
//    // FILE *fp0 = fopen("encrypted_output", "wb");
//    // fwrite(seal_out, 1, seal_out_size, fp0);
//    // fclose(fp0);
//
//    EVP_PKEY_free(pubkey);
//    EVP_PKEY_free(prikey);



//	std::cout << "------ start test ------" << std::endl;
//
//	if (SQLITE_OK != sqlite3_open("/t/lock.db", &db)) {
//		std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//		return 1;
//	}
//	std::cout << "Open database successfully!" << std::endl << std::endl;
//
//	if (0
//			>= add_user("username", "credential", "imei12453246432", 12454,
//					45476, 324567732, 2435676542343, 0, 0)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//
//	User user;
//
//	if (0 >= get_user(4, user)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//	user.setUsername("hello world!!!!!!");
//	if (0 >= update_user(user)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//	std::vector<User> users;
//	if (0 >= list_user(users)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//
//	if (0
//			>= add_log(2, 12454232443, 2, "这个是日志内容啊啊啊啊啊啊啊啊", 0,
//					"这个是备注！3443134546")) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//
//	std::vector<Log> logs;
//	if (0 >= list_log(logs)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//
//	if (0 >= add_permission(2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)) {
//		std::cerr << "Query " << "th sql error!" << std::endl;
//		return -1;
//	}
//
//	std::cout << "All sql query successfully!" << std::endl;

	polling->join();
	log_info("long_polling thread ended!");
	delete polling;
	sqlite3_close(db);
	network::uninit();
	return 0;
}

