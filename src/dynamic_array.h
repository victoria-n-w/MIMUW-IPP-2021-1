#ifndef __DYNAMIC_ARAY_H
#define __DYNAMIC_ARAY_H

#include <stdlib.h>

typedef struct dynamic_array dynamic_array_t;

dynamic_array_t *new_dynamic_array(size_t init_size);
/**
 * safely destroy dynamic array
 */
void destroy_dynamic_array(dynamic_array_t *arr);

/**
 * pops last element from dynamic array
 * and returns pointer to this element
 *
 * returns NULL if arr is empty
 */
void *dynamic_array_pop(dynamic_array_t *arr);

/**
 * push *element at the end of dynamic array
 * exists the program with signal 1 if any malloc failed
 */
void dynamic_array_push(dynamic_array_t *arr, void *element);

void *dynamic_array_get(dynamic_array_t *arr, size_t i);

size_t dynamic_array_get_size(dynamic_array_t *arr);
#endif