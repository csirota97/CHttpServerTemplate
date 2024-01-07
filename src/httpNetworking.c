#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

char *getHeader(const char *requestHeaderLines, const char *headerToFind)
{
    char *headerValue = malloc(BUFFER_SIZE);
    char *line = malloc(BUFFER_SIZE);
    line = strtok(requestHeaderLines, "\r\n");

    while (line != NULL)
    {

      if (strcasestr(line, headerToFind) != 0)
      {

        headerValue = strtok(line, ": ");
        headerValue = strtok(NULL, ": ");
        break;
      }
      else 
      {
        line = strtok(NULL, "\r\n");
      }
    }
    return headerValue;
}

int getParamCount(char *uri) {
  int paramCount = 0;
  for (int i = 0; i < strlen(uri); i++) {
    if (uri[i] == '?' || uri[i] == '&')
    {
      paramCount++;
    }
  }
  return paramCount;
}

void getParams(char *uri, int paramCount, char paramsArr[paramCount][2][strlen(uri)])
{
  if (paramCount == 0) {
    return;
  }
  char uriCopy[strlen(uri)];
  char paramsStr[strlen(uri)];

  for (int i = 0; i < strlen(uri); i++) {
    uriCopy[i] = uri[i];
  }

  for (int i = 0; i < strlen(uri); i++) {
    if (uriCopy[i] == '?') {
      strncpy(paramsStr, uriCopy+i+1, strlen(uriCopy)-i);
      break;
    }
    if (i == strlen(uriCopy) - 1) {
      return;
    }
  }
  
  char *paramSavePtr;
  char *paramValueSavePtr;

  char *param = strtok_r(paramsStr, "&", &paramSavePtr);

  char *paramKey = strtok_r(param, "=", &paramValueSavePtr);
  for (int i = 0; i < strlen(paramKey); i++) {
    paramsArr[0][0][i] = paramKey[i];
  }
  paramsArr[0][0][strlen(paramKey)] = '\0';
  char *paramValue = strtok_r(NULL, "=", &paramValueSavePtr);strtok_r(param, "=", &paramValueSavePtr);
  for (int i = 0; i < strlen(paramValue); i++) {
    paramsArr[0][1][i] = paramValue[i];
  }
  paramsArr[0][1][strlen(paramValue)] = '\0';
  for (int i = 1; i < paramCount; i++) {
    char *param = strtok_r(NULL, "&", &paramSavePtr);

    char *paramKey = strtok_r(param, "=", &paramValueSavePtr);
    for (int j = 0; j < strlen(paramKey); j++) {
      paramsArr[i][0][j] = paramKey[j];
    }
    paramsArr[i][0][strlen(paramKey)] = '\0';
    char *paramValue = strtok_r(NULL, "=", &paramValueSavePtr);strtok_r(param, "=", &paramValueSavePtr);
    for (int j = 0; j < strlen(paramValue); j++) {
      paramsArr[i][1][j] = paramValue[j];
    }
    paramsArr[i][1][strlen(paramValue)] = '\0';
  }
  return;
}

int isURIOnRoute(char *path, char *uri)
{
  char uriCopy[strlen(uri) + 1];
  for (int i = 0; i < strlen(uri); i++) {
    uriCopy[i] = uri[i];
  }

  for (int i = 0; i < strlen(uri); i++) {
    if (uri[i] == '?') {
      uri[i] = '\0';
      break;
    }
  }

  if (strcmp(path, uri) == 0)
  {
    for (int i = 0; i < strlen(uriCopy); i++) {
      uri[i] = uriCopy[i];
    }
    return 1;
  }
  char *uriC = malloc(sizeof uri);
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
  
  for (int i = 0; i < strlen(uriCopy); i++) {
    uri[i] = uriCopy[i];
  }
  return retVal;
}