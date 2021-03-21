#include "safe_funcs.h"

#include <stdio.h>
#include <stdlib.h>

void *safe_malloc(size_t size) {
  void *res = malloc(size);
  if (res == NULL) {
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
  }
  return res;
}

void *safe_realloc(void *what, size_t size) {
  void *res = realloc(what, size);
  if (res == NULL) {
    fprintf(stderr, "Could not realloc memory\n");
    exit(1);
  }
  return res;
}
