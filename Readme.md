# Basic HTTP Server
## Adding custom routers
- Create new file in `src/routers` directory
  - Define handler function with return type `char *`
    - Handler should accept 1 parameter `const char **args`

  - Sample router definition below:

```c
char *r1GET(const char **args) {
  printf("Hello World\nROUTE 1 GET, %s\n", args[0]);
  return "";
}

char *r1POST(const char **args) {
  printf("Hello World\nROUTE 1 POST, %s\n", args[0]);
  return "";
}

char *r1DELETE(const char **args) {
  printf("Hello World\nROUTE 1 DELETE, %s\n", args[0]);
  return "";
}

struct Router sampleRouter = {
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

- In `src/main.c`, identify `struct Router initialRouter;`
  - After `initialRouter` is defined add `memcpy(&initialRouter, &<custom_router_name>, sizeof(<custom_router_name>));` for the first custom router
  - Subsequent custom routers can be added by using the `void insertRouter(struct Router *firstRouter, struct Router *newRouter)` function, passing in the initialRouter, and the custom router. 
  - The following is an example defining 3 routers:
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