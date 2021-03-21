#ifndef _SAFE_FUNCS_H
#define _SAFE_FUNCS_H

#include <stdlib.h>
/**
 * safely malloc
 * exists the program with signal 1 if malloc failed
 * TODO: maybe write to stderr
 */
void *safe_malloc(size_t size);

void *safe_realloc(void *what, size_t size);

#endif