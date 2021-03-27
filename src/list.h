#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include <stdlib.h>

#include "dynamic_array.h"

typedef struct list list_t;

/**
 * initialize new, empty list
 */
list_t *new_list();

/**
 * destroys empty list
 *
 * if l is not empty, exits the program with signal 1
 */
void destroy_list(list_t *l);

/**
 * append element e at the end of the list l
 */
void list_append(list_t *l, void *e);

/**
 * concatenates two lists together
 * clears the second list in the process
 *
 * last argument specifiec whter to destroy second list,
 * after it is emptied
 */
list_t *list_concat(list_t *a, list_t *b, bool destroy_second);

/**
 * pops the first element from the list l
 * return NULL if list is empty
 */
void *list_pop_front(list_t *l);

/**
 * converts list to dynamic array.
 * Destroys list in the process, freeing the memory
 */
dynamic_array_t *list_to_dynamic_array(list_t *l, size_t lenght);

/**
 * return the first element, without removing it
 */
void *list_peek(list_t *l);

bool list_is_empty(list_t *l);

#endif