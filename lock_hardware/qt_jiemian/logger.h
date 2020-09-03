/*
 * logger.h
 *
 *  Created on: Jul 14, 2020
 *      Author: davies
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdint.h>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstdlib> // for sprintf

void inline log_time(std::ostream &os) {
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);
	char foo[24];
	sprintf(foo, "%04d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, // @suppress("Invalid arguments")
			tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	os << foo << " ";
//    os << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " ";
}

template<class ... Types>
void log_err(Types ... args) {
	log_time(std::cout);
	std::cerr << "Err: ";
	int dummy[sizeof...(Types)] = { (std::cout << args, 0)... };
	std::cerr << std::endl;
}
template<class ... Types>
void log_info(Types ... args) {
	log_time(std::cout);
	std::cout << "Inf: ";
	int dummy[sizeof...(Types)] = { (std::cout << args, 0)... };
	std::cout << std::endl;
}

#endif /* LOGGER_H_ */
