#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#include "http.h"

void init_string(string *s)
{
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL)
    {
        fprintf(stderr, "malloc() failed\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, string *s)
{
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL)
    {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}
void get(const char* url)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        string s;
        init_string(&s);

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {   
            fprintf(stderr, "Error %s", curl_easy_strerror(res));
            return;
        }

        printf("Data: %s\n", s.ptr);
        fflush(stdout);
        free(s.ptr);

        curl_easy_cleanup(curl);
    }
}

void post(const char* url, const char* data)
{
    CURL* curl;
    CURLcode code;

    curl = curl_easy_init();
    if (curl)
    {
        string s;
        init_string(&s);

        struct curl_slist* headers = NULL;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        code = curl_easy_perform(curl);
        if (code != CURLE_OK)
        {
            fprintf(stderr, "Error %s", curl_easy_strerror(code));
            return;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        printf("@todos POST\n");
        printf("%s\n", s.ptr);
        free(s.ptr);
    }
}

void put(const char* url, const char* data)
{
    CURL* curl;
    CURLcode code;

    curl = curl_easy_init();
    if (curl)
    {
        string s;
        init_string(&s);

        struct curl_slist* headers = NULL;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_PUT, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        code = curl_easy_perform(curl);
        if (code != CURLE_OK)
        {
            fprintf(stderr, "Error %s", curl_easy_strerror(code));
            return;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        printf("@todos/1 PUT\n");
        printf("%s\n", s.ptr);
        free(s.ptr);
    }
}

void delete(const char* url)
{
    CURL* curl;
    CURLcode code;

    curl = curl_easy_init();
    if (curl)
    {
        string s;
        init_string(&s);

        struct curl_slist* headers = NULL;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        code = curl_easy_perform(curl);
        if (code != CURLE_OK)
        {
            fprintf(stderr, "Error %s", curl_easy_strerror(code));
            return;
        }
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        printf("@todos/1 DELETE\n");
        printf("%s\n", s.ptr);
        free(s.ptr);
    }
}