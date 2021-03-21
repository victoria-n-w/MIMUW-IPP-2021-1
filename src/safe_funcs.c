#include "safe_funcs.h"

#include <stdlib.h>

void *safe_malloc(size_t size) {
  void *res = malloc(size);
  if (res == NULL) exit(1);
  return res;
}