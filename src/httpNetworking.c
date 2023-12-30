#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

char *getHeader(const char *requestHeaderLines, const char *headerToFind)
{
    printf("q\n");
    char *headerValue = malloc(BUFFER_SIZE);
    printf("w\n");
    char *line = malloc(BUFFER_SIZE);
    printf("1\n");
    line = strtok(requestHeaderLines, "\r\n");
    printf("2\n");

    while (line != NULL)
    {

      if (strcasestr(line, headerToFind) != 0)
      {

        headerValue = strtok(line, ": ");
    printf("5\n");
        headerValue = strtok(NULL, ": ");
        break;
      }
      else 
      {
    printf("7\n");
        line = strtok(NULL, "\r\n");
    printf("8\n");
      }
    }
    printf("9\n");
    // free(line);
    printf("10\n");
    return headerValue;
}

int isURIOnRoute(char *path, char *uri)
{
  if (strcmp(path, uri) == 0)
  {
    return 1;
  }
  printf("e\n");
  char *uriC = malloc(sizeof uri);
  printf("r\n");
  char *pathC = malloc(sizeof path);
  strcpy(uriC, uri);
  strcpy(pathC, path);

  char *uriSavePointer, *pathSavePointer;

  char* uriTokens = strtok_r(uriC, "/", &uriSavePointer);
  char* pathTokens = strtok_r(pathC, "/", &pathSavePointer);
  int retVal = 1;

  while (uriTokens != NULL && pathTokens != NULL)
  {
    if(strcmp(uriTokens, pathTokens) != 0) {
      if (pathTokens[0] != '<' || pathTokens[strlen(pathTokens)-1] != '>')
      {
        retVal = 0;
        break;
      }
    }

    uriTokens = strtok_r(NULL, "/", &uriSavePointer);
    pathTokens = strtok_r(NULL, "/", &pathSavePointer);
  }

  if ((uriTokens == NULL && pathTokens != NULL) || (uriTokens != NULL && pathTokens ==  NULL))
  {
    retVal = 0;
  }
  
  return retVal;
}