// DELETE THIS FILE
char *r3GET(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 3 GET");
  return "HELLO";
}

char *r3POST(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 3 POST");
  return "HELLO";
}

char *r3PUT(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 3 PUT");
  return "HELLO";
}

char *r3DELETE(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 3 DELETE");
  return "HELLO";
}


struct Router thirdRouter = {
  4,
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