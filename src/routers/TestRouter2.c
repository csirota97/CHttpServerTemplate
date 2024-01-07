// DELETE THIS FILE
char *r2GET(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 2 GET");
  return "HELLO";
}

char *r2POST(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 2 POST");
  return "HELLO";
}

char *r2PUT(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 2 PUT");
  return "HELLO";
}

char *r2DELETE(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 2 DELETE");
  return "HELLO";
}


struct Router secondRouter = {
  4,
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