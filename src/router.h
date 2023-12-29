#include "methods.h"

typedef char *(*Handler) (const char *args[]);

typedef struct Route {
  char *method;
  Handler handler;
};

typedef struct Router
{
  struct Route routes[METHOD_COUNT];
  char *path; 
  struct Router *nextRouter;
};
