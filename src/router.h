#include "methods.h"

typedef char *(*Handler) (
  char *uri,
  int paramCount,
  char paramsArr[paramCount][2][strlen(uri)], // [array [param components [key string][value string]]]
  int contentLength,
  char *content);

typedef struct Route {
  char *method;
  Handler handler;
};

typedef struct Router
{
  int methodsCount; 
  struct Route routes[6];
  char *path;
  struct Router *nextRouter;
};
