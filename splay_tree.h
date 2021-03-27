#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

#include <stdbool.h>

#include "dynamic_array.h"

typedef struct splay_tree splay_tree_t;

splay_tree_t *new_splay_tree(int (*cmp)(void *, void *));

void destroy_splay_tree(splay_tree_t *t, void (*destroy_node)(void *));

/**
 * inserts element into the tree
 * returns pointer to this element
 */
void *splay_tree_insert(splay_tree_t *tree, void *element);

/**
 * maps the tree to the dynamic array
 * using function func
 */
dynamic_array_t *splay_tree_map(splay_tree_t *tree, void *(*func)(void *));

#endif