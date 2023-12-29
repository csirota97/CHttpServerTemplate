// DELETE THIS FILE
char *r2GET(const char **args) {
  printf("Hello World\nROUTE 2 GET, %s\n", args[0]);
  return "HELLO";
}

char *r2POST(const char **args) {
  printf("Hello World\nROUTE 2 POST, %s\n", args[0]);
  return "HELLO";
}

char *r2PUT(const char **args) {
  printf("Hello World\nROUTE 2 PUT, %s\n", args[0]);
  return "HELLO";
}

char *r2DELETE(const char **args) {
  printf("Hello World\nROUTE 2 DELETE, %s\n", args[0]);
  return "HELLO";
}


struct Router secondRoute = {
  {
    {
      "GET",
      *r2GET
    },
    {
      "POST",
      *r2POST
    },
    {
      "PUT",
      *r2PUT
    },
    {
      "DELETE",
      *r2DELETE
    }
  },
  "/route2",
  NULL,
};