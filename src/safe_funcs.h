#ifndef _SAFE_FUNCS_H
#define _SAFE_FUNCS_H

#include <stdlib.h>

void *safe_malloc(size_t size);

void *safe_realloc(void *what, size_t size);

#endif