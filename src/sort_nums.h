#ifndef _SORT_NUMS_H
#define _SORT_NUMS_H

#include "dynamic_array.h"
/**
 * copies arr
 * and sorts numbers inside it
 * returns pointer to the created copy
 *
 * uses heap-sort
 */
dynamic_array_t *sort_numbers(dynamic_array_t *arr);

#endif