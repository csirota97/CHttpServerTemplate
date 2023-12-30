// DELETE THIS FILE
char *r3GET(const char **args) {
  printf("Hello World\nROUTE 3 GET, %s\n", args[0]);
  return "HELLO";
}

char *r3POST(const char **args) {
  printf("Hello World\nROUTE 3 POST, %s\n", args[0]);
  return "HELLO";
}

char *r3PUT(const char **args) {
  printf("Hello World\nROUTE 3 PUT, %s\n", args[0]);
  return "HELLO";
}

char *r3DELETE(const char **args) {
  printf("Hello World\nROUTE 3 DELETE, %s\n", args[0]);
  return "HELLO";
}


struct Router thirdRouter = {
  {
    {
      "GET",
      *r3GET
    },
    {
      "POST",
      *r3POST
    },
    {
      "PUT",
      *r3PUT
    },
    {
      "DELETE",
      *r3DELETE
    }
  },
  "/route3",
  NULL
};