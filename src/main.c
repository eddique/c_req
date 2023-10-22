#include <stdlib.h>
#include "common.h"
void *thread_function(void *arg)
{
    printf("Thread is running\n");
    return NULL;
}
int main(void)
{
    const char *url_get = "https://jsonplaceholder.typicode.com/todos";
    get(url_get);
    const char *url_post = "https://jsonplaceholder.typicode.com/todos";
    const char *data_post = "title=Hello, World!&message=A todo from C!";
    post(url_post, data_post);

    const char *url_put = "https://jsonplaceholder.typicode.com/todos/1";
    const char *data_put = "title=Updated Message!&message=A todo from C!";
    put(url_put, data_put);

    const char *url_delete = "https://jsonplaceholder.typicode.com/todos/1";
    delete (url_delete);
    
    return 0;
}