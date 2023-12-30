#include "methods.h"

typedef char *(*Handler) (const char *args[]);

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
