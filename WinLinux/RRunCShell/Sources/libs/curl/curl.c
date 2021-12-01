#include "curl.h"

/* callback for curl fetch */
size_t curl_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;							 /* calculate buffer size */
	struct curl_fetch_st *p = (struct curl_fetch_st *)userp; /* cast pointer to fetch struct */

	/* expand buffer using a temporary pointer to avoid memory leaks */
	char *temp = realloc(p->payload, p->size + realsize + 1);

	/* check allocation */
	if (temp == NULL)
	{
		/* this isn't good */
		fprintf(stderr, "ERROR: Failed to expand buffer in curl_callback");
		/* free buffer */
		free(p->payload);
		/* return */
		return 1;
	}

	/* assign payload */
	p->payload = temp;

	/* copy contents to buffer */
	memcpy(&(p->payload[p->size]), contents, realsize);

	/* set new buffer size */
	p->size += realsize;

	/* ensure null termination */
	p->payload[p->size] = 0;

	/* return size */
	return realsize;
}

/* fetch and return url body via curl */
CURLcode curl_fetch_url(CURL *curl, struct curl_fetch_st *fetch, int timeout)
{
	CURLcode rcode; /* curl result code */

	/* init payload */
	fetch->payload = (char *)calloc(1, sizeof(fetch->payload));

	/* check payload */
	if (fetch->payload == NULL)
	{
		/* log error */
		fprintf(stderr, "ERROR: Failed to allocate payload in curl_fetch_url");
		/* return error */
		return CURLE_FAILED_INIT;
	}

	/* init size */
	fetch->size = 0;

	/* set calback function */
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback);

	/* pass fetch struct pointer */
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)fetch);

	/* set default user agent */
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

	/* set timeout */
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

	/* set ssl */
	curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

	/* enable location redirects */
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);

	/* set maximum allowed redirects */
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 1);

	/* fetch the url */
	rcode = curl_easy_perform(curl);

	/* return */
	return rcode;
}

CURLcode btc_rpc(struct curl_fetch_st *cfst, int timeout, const char *url, const char *userpwd, const char *data)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *headers = NULL;

	if ((curl = curl_easy_init()) == NULL)
	{
		fprintf(stderr, "ERROR: Failed to create curl handle in fetch_session");
		return CURLE_FAILED_INIT;
	}

	headers = curl_slist_append(headers, "content-type: text/plain;");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(data));
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
	curl_easy_setopt(curl, CURLOPT_USERPWD, userpwd);

	/* Perform the request, res will get the return code */
	res = curl_fetch_url(curl, cfst, timeout);
	/* Check for errors */
	//if (res != CURLE_OK)
	//fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

	/* free headers */
	curl_slist_free_all(headers);

	/* always cleanup */
	curl_easy_cleanup(curl);

	return res;
}