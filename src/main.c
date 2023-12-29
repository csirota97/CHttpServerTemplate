#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include "main.h"
#include "httpResponses.h"
#include "constants.h"
#include "httpNetworking.h"
#include "httpNetworking.c"
#include "methods.h"
#include "router.h"

#include "routers/TestRouter1.c"
#include "routers/TestRouter2.c"


void insertRouter(struct Router *firstRouter, struct Router *newRouter)
{
  struct Router *ptr = firstRouter; 
  while(ptr->nextRouter != NULL)
  {
    ptr = ptr->nextRouter;
  }
  ptr->nextRouter = newRouter;
}

int isAuthKeyValid(char *authn)
{
  if (strncmp(authn, AUTH_KEY, AUTH_KEY_LENGTH) != 0 ||
      (strncmp(authn, AUTH_KEY, AUTH_KEY_LENGTH) == 0 && authn[AUTH_KEY_LENGTH] != '\0' && authn[AUTH_KEY_LENGTH] != '\r'))
  {
    return 0;
  }
  return 1;
}

int processRequest(char* buffer, struct Router initialRouter)
{
  char method[BUFFER_SIZE], uri[BUFFER_SIZE], version[BUFFER_SIZE], authLabel[BUFFER_SIZE], requestCopy[BUFFER_SIZE], overflow[BUFFER_SIZE];

  sscanf(buffer, "%s %s %s\r\n%s", method, uri, version, overflow);
  strcpy(requestCopy, buffer);
  char *authn = getHeader(buffer, AUTH_LABEL);
  strcpy(buffer, requestCopy);

  if (isAuthKeyValid(authn) == 0)
  {
    return UNAUTHORIZED;
  }

  struct Router *routerPtr = &initialRouter;
  int routeFound = 0;
  int methodValid = 0;
  while (routerPtr != NULL && routeFound < 1)
  {
    if (isURIOnRoute(routerPtr[0].path, uri) == 1)
    {
      routeFound = 1;
      for (int i = 0; i < METHOD_COUNT && methodValid < 1; i++)
      {
        struct Route *curRoute = &routerPtr->routes[i];
        if (curRoute[0].method != NULL && strcmp(curRoute[0].method, method) == 0)
        {
          methodValid = 1;
          const char *argsp[10] = {"TEST ARGS"};
          char *retVal = curRoute[0].handler(argsp);
        } 
      }
    }
    routerPtr = routerPtr->nextRouter;
  }

  if (routeFound == 0)
  {
    return NOT_FOUND;
  } else if (methodValid == 0)
  {
    return NO_METHOD;
  }


  // HANDLE DIFFERENT ROUTES AND METHODS
  return SUCCESS_200;
}

int writeResponse(int successStatus, int newsockfd)
{
  int valwrite = 0;
  switch (successStatus)
  {
    case UNAUTHORIZED:
      valwrite = write(newsockfd, resp_401, strlen(resp_401));
      break;
    case NOT_FOUND:
      valwrite = write(newsockfd, resp_404, strlen(resp_404));
      break;

    case NO_METHOD:
      valwrite = write(newsockfd, resp_405, strlen(resp_405));
      break;

    case SUCCESS_200:
      valwrite = write(newsockfd, resp_200, strlen(resp_200));
      printf("Connection authenticated\n");
      
      break;
    default:
      break;
  }
  if (valwrite < 0)
  {
    perror("webserver (write)");
    return valwrite;
  }


  close(newsockfd);
  return valwrite;
}

int main(int argc, char *argv[]) {
  int PORT;
  if (argc > 1) {
    sscanf(argv[1], "%d", &PORT);
  } else {
    PORT = 8080;
  }

  struct Router initialRouter;
  memcpy(&initialRouter, &firstRoute, sizeof(firstRoute));
  insertRouter(&initialRouter, &secondRoute);

  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    perror("webserver (socket)");
    return 1;
  }

  printf("socket created successfully\n");

  struct sockaddr_in host_addr;
  int host_addrlen = sizeof(host_addr);

  host_addr.sin_family = AF_INET;
  host_addr.sin_port = htons(PORT);
  host_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  // Create client address
  struct sockaddr_in client_addr;
  int client_addrlen = sizeof(client_addr);
  
  if (bind(sockfd, (struct sockaddr *)&host_addr, host_addrlen) != 0)
  {
    perror("webserver (bind)");
    return 1;
  }
  printf("socket successfully bound to %u:%d \n", host_addr.sin_addr.s_addr, PORT);

  if (listen(sockfd, SOMAXCONN) != 0)
  {
    perror("webserver (listen)");
    return 1;
  }
  printf("socket listening for connections\n");

  for (;;)
  {
    char buffer[BUFFER_SIZE];
    for (int i = 0; i<BUFFER_SIZE; i++)
    {
      buffer[i] = '\0';
    }

    int newsockfd = accept(sockfd, (struct sockaddr *)&host_addr, (socklen_t *)&host_addrlen);
    if (newsockfd < 0)
    {
      perror("webserver (accept)");
      continue;
    }
    printf("connection accepted\n");

    int sockn = getsockname(newsockfd, (struct sockaddr *)&client_addr,
                            (socklen_t *)&client_addrlen);
    if (sockn < 0) {
        perror("webserver (getsockname)");
        continue;
    }

    int valread = read(newsockfd, buffer, BUFFER_SIZE);
    if (valread < 0)
    {
      perror("webserver (read)");
      continue;
    }

    int successStatus = processRequest(buffer, initialRouter);
    int valwrite = writeResponse(successStatus, newsockfd);
    if (valwrite < 0)
    {
      continue;
    }
  }

  return 0;
}