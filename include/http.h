#ifndef c_req_http_h
#define c_req_http_h
#include <curl/curl.h>
typedef struct {
  char *ptr;
  size_t len;
} string;
void get(const char* url);
void post(const char* url, const char* data);
void put(const char* url, const char* data);
void delete(const char* url);
#endif