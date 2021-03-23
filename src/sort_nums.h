#ifndef _SORT_NUMS_H
#define _SORT_NUMS_H

#include <stdbool.h>

#include "dynamic_array.h"
/**
 * copies arr
 * and sorts numbers inside it
 * returns pointer to the created copy
 *
 * last arguments is comparator
 * the comparator(a, b) has to return true if a<b
 *
 * uses heap-sort
 */
dynamic_array_t *sort_numbers(dynamic_array_t *arr,
                              bool (*cmp)(void *, void *));

/**
 * returns true if a < b
 * (compares long double numbers)
 */
bool ld_comparator(void *a, void *b);

#endif