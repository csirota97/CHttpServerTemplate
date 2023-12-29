// DELETE THIS FILE

char *r1GET(const char **args) {
  printf("Hello World\nROUTE 1 GET, %s\n", args[0]);
  return "HELLO";
}

char *r1POST(const char **args) {
  printf("Hello World\nROUTE 1 POST, %s\n", args[0]);
  return "HELLO";
}

char *r1DELETE(const char **args) {
  printf("Hello World\nROUTE 1 DELETE, %s\n", args[0]);
  return "HELLO";
}


struct Router firstRoute = {
  {
    {
      "GET",
      *r1GET
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
  "/route1/<hello world>",
  NULL,
};