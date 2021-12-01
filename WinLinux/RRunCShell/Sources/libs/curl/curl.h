#ifndef CURL_H
#define CURL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

/* holder for curl fetch */
struct curl_fetch_st
{
    char *payload;
    size_t size;
};

/* callback for curl fetch */
size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp);

/* fetch and return url body via curl */
CURLcode curl_fetch_url(CURL *curl, struct curl_fetch_st *fetch, int timeout);

CURLcode btc_rpc(struct curl_fetch_st *cfst, int timeout, const char *url, const char *userpwd, const char *data);

#endif