// DELETE THIS FILE

char *r4GET(const char **args) {
  printf("Hello World\nROUTE 1 GET, %s\n", args[0]);
  return "<html><body><h1>HELLO</h1></body></html>";
}


struct Router fourthRouter = {
  1,
  {
    {
      "PUT",
      *r4GET
    },
  },
  "/route1/<hello world>",
  NULL,
};