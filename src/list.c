#include "list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "safe_funcs.h"

typedef struct list_node list_node_t;

struct list_node {
  void *element;
  list_node_t *next;
};

typedef struct list {
  list_node_t *first_node, *last_node;
} list_t;

list_t *new_list() {
  list_t *res = safe_malloc(sizeof(list_t));
  res->first_node = NULL;
  res->last_node = NULL;
  return res;
}

void destroy_list(list_t *l) {
  if (l == NULL) return;

  if (l->first_node != NULL) {
    fprintf(stderr, "Cannot destroy non-empty list\n");
    exit(1);
  }

  free(l);
}

static void invalid_list() {
  fprintf(stderr, "List cannot be NULL\n");
  exit(1);
}

void list_append(list_t *l, void *e) {
  if (l == NULL) invalid_list();

  list_node_t *new_node = safe_malloc(sizeof(list_node_t));
  new_node->next = NULL;
  new_node->element = e;

  if (l->last_node == NULL) {
    // l is empty
    l->first_node = new_node;
    l->last_node = new_node;
  } else {
    l->last_node->next = new_node;
    l->last_node = new_node;
  }
}

list_t *list_concat(list_t *a, list_t *b, bool destroy_second) {
  if (a == NULL || b == NULL) invalid_list();

  if (b->first_node == NULL) {
    if (destroy_second) destroy_list(b);
    return a;
  }

  if (a->first_node == NULL) {
    a->first_node = b->first_node;
    a->last_node = b->last_node;
    b->first_node = b->last_node = NULL;
    if (destroy_second) destroy_list(b);
    return a;
  }

  a->last_node->next = b->first_node;
  a->last_node = b->last_node;
  b->first_node = b->last_node = NULL;
  if (destroy_second) destroy_list(b);
  return a;
}

void *list_pop_front(list_t *l) {
  if (l == NULL) invalid_list();

  if (l->first_node == NULL) {
    return NULL;
  }

  list_node_t *node = l->first_node;

  if (l->first_node == l->last_node) {
    l->first_node = l->last_node = NULL;
  } else {
    l->first_node = node->next;
  }

  void *res = node->element;
  free(node);
  return res;
}

dynamic_array_t *list_to_dynamic_array(list_t *l, size_t n) {
  dynamic_array_t *res = new_dynamic_array(n);
  void *element;

  while ((element = list_pop_front(l)) != NULL) {
    dynamic_array_push(res, element);
  }

  destroy_list(l);
  return res;
}

bool list_is_empty(list_t *l) { return l->first_node == NULL; }

void *list_peek(list_t *l) {
  if (l == NULL) invalid_list();
  return l->first_node;
}