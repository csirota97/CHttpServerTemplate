# Basic HTTP Server
## Adding custom routers
- Create new file in [`src/routers`](https://github.com/csirota97/CHttpServerTemplate/tree/master/src/routers) directory
  - Define handler function with return type `char *`
    - Handler should accept 5 parameters
      - `char *uri`
        - URI of requested endpoint, includig query parameters
      - `int paramCount`
        - number of query parameters present in the URI
      - `char paramsArr[paramCount][2][strlen(uri)]`
        - an array of the query parameters, represented by arrays of 2 strings, consisting of a key and a value at indexes 0 and 1 respectively
          - ex:<br> `[["Key1", "Value1"], ["Key2", "Value2"]]`
      - `int contentLength`
        - length of request body
      - `char *content`
        - request body contents
  - A router, by default, can accept 6 methods
    - If a path requires more than 6 HTTP methods, subsequent HTTP methods can be defined in a new router with the same path.

  - Sample router definition below:

```c
char *r1GET(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("URI %s\n", uri);
  printf("PARAMS_COUNT %d\n", paramCount);
  printf("PARAMS_ARR (first param) [%s]=[%s]\n", paramsArr[0][0], paramsArr[0][1], paramsArr[1][0], paramsArr[1][1]);
  printf("CONTENT_LENGTH %d\n", contentLength);
  printf("CONTENT %s\n", content);

  return "";
}

char *r1POST(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 1 POST, %s\n", args[0]);
  return "";
}

char *r1DELETE(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 1 DELETE, %s\n", args[0]);
  return "";
}

struct Router sampleRouter = {
  3, // COUNT OF METHODS AVAILABLE ON PATH
  {
    {
      "GET", // HTTP METHOD
      *r1GET // POINTER TO HANDLER
    },
    {
      "POST",
      *r1POST
    },
    {
      "DELETE",
      *r1DELETE
    }
  },
  "/route1", // PATH FOR RESOURCE
  NULL, // NEXT ROUTER - LEAVE AS NULL
};
``````

- In [`src/main.c`](https://github.com/csirota97/CHttpServerTemplate/blob/master/src/main.c), identify [`struct Router initialRouter;`](https://github.com/csirota97/CHttpServerTemplate/blob/master/src/main.c#L143)
  - After `initialRouter` is defined add `memcpy(&initialRouter, &<custom_router_name>, sizeof(<custom_router_name>));` for the first custom router
  - Subsequent custom routers can be added by using the `void insertRouter(struct Router *firstRouter, struct Router *newRouter)` function, passing in the initialRouter, and the custom router. 
  - The following is an example defining 3 routers or can be viewed in context [here](https://github.com/csirota97/CHttpServerTemplate/blob/master/src/main.c#L144-L147):
    - newRouter1
    - newRouter2
    - newRouter3 
```c
int main(int argc, char *argv[])
{
  ...
  struct Router initialRouter;

  memcpy(&initialRouter, &newRouter1, sizeof(newRouter1));

  insertRouter(&initialRouter, &newRouter2);

  insertRouter(&initialRouter, &newRouter3);
  ...
}

```
