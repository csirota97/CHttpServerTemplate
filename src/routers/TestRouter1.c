// DELETE THIS FILE

// uri, // URI with stripped out parameters
//             uriBackup, // unmodified URI
//             paramsArr, // request parameters
//             sizeof(paramsArr)/sizeof(paramsArr[0]), // number of request parameters
//             content, // body
//             sizeof(content), // length of body
char *r1GET(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("URI %s\n", uri);
  printf("PARAMS_COUNT %d\n", paramCount);
  printf("PARAMS_ARR (first param) [%s]=[%s]\n", paramsArr[0][0], paramsArr[0][1], paramsArr[1][0], paramsArr[1][1]);
  printf("CONTENT_LENGTH %d\n", contentLength);
  printf("CONTENT %s\n", content);

  return "<html><body><h1>HELLO</h1></body></html>";
}

char *r1POST(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 1 POST, %s\n%d\n%s\n%d\n%s\n", uri, paramCount, paramsArr[0][0],contentLength, content );
  return "HELLO";
}

char *r1DELETE(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)], int contentLength, char *content) {
  printf("Hello World\nROUTE 1 DELETE, %s\n%d\n%s\n%d\n%s\n", uri, paramCount, paramsArr[0][0],contentLength, content );

  return "HELLO";
}


struct Router firstRouter = {
  3,
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