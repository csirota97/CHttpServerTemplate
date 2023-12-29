#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"

/**
 * requestHeaderLines
 * headerToFind
*/
char *getHeader(const char *requestHeaderLines, const char *headerToFind);

/**
 * path
 * uri
 * returns 0 if not uri is not on path, else 1
*/
int isURIOnRoute(char *path, char *uri);
