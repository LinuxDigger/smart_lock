/*
 * network.cpp
 *
 *  Created on: Jul 15, 2020
 *      Author: davies
 */

#include <curl/curl.h>
#include "network.h"

namespace network {

bool inti() {
	/* In windows, this will init the winsock stuff */
	return CURLE_OK == curl_global_init(CURL_GLOBAL_ALL);
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, std::string *s) {
	unsigned int len = size * nmemb;
	*s += std::string((char const*) ptr, 0, len);
	return len;
}

int64_t ajax(char const *url, char const *body, struct curl_slist *hs,
		std::string &response) {
	CURL *curl;
	CURLcode res;
	/* get a curl handle */
	curl = curl_easy_init();
	if (!curl) {
		return -1;
	}
	/* First set the URL that is about to receive our POST. This URL can
	 just as well be a https:// URL if that is what should receive the
	 data. */
	curl_easy_setopt(curl, CURLOPT_URL, url);
	if (hs)
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
	if (body)
		/* Now specify the POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body);
	response.clear();
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
	/* Perform the request, res will get the return code */
	if (CURLE_OK != curl_easy_perform(curl)) {
		return -2;
	}
	int64_t status = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);

	/* always cleanup */
	curl_easy_cleanup(curl);
	return status;
}

bool uninit() {
	curl_global_cleanup();
	return true;
}

}
