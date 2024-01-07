// DELETE THIS FILE

char *r4PUT(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 1 PUT");
  return "<html><body><h1>HELLO</h1></body></html>";
}


struct Router fourthRouter = {
  1,
  {
    {
      "PUT",
      *r4PUT
    },
  },
  "/route1/<hello world>",
  NULL,
};