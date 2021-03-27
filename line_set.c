#include "line_set.h"

#include <stdio.h>

#include "heap_sort.h"
#include "line_record.h"
#include "list.h"
#include "safe_funcs.h"
#include "splay_tree.h"

typedef struct line_set {
  splay_tree_t *tree;
} line_set_t;

typedef struct tree_node {
  list_t *line_numbers;
  line_record_t *rec;
} tree_node_t;

static tree_node_t *new_tree_node(line_record_t *rec) {
  tree_node_t *res = safe_malloc(sizeof(tree_node_t));
  res->rec = rec;
  res->line_numbers = new_list();
  return res;
}

static int tree_node_comparator(void *a, void *b) {
  return line_rec_comparator(((tree_node_t *)a)->rec, ((tree_node_t *)b)->rec);
}

line_set_t *new_line_set() {
  line_set_t *res = safe_malloc(sizeof(line_set_t));
  res->tree = new_splay_tree(tree_node_comparator);
  return res;
}

static void destroy_node(void *x) {
  tree_node_t *node = x;
  uint64_t *number;

  while ((number = list_pop_front(node->line_numbers)) != NULL) {
    free(number);
  }

  destroy_list(node->line_numbers);
  destroy_line_record(node->rec);
  free(x);
}

void destroy_line_set(line_set_t *set) {
  destroy_splay_tree(set->tree, destroy_node);
  free(set);
}

void line_set_insert(line_set_t *set, line_record_t *rec) {
  tree_node_t *new_node = new_tree_node(rec);

  tree_node_t *res_node = splay_tree_insert(set->tree, new_node);
  uint64_t *new_line_number = safe_malloc(sizeof(uint64_t));
  *new_line_number = line_rec_get_number(rec);

  if (!list_is_empty(res_node->line_numbers)) {
    // similar line has been inserted into the tree before
    // we have to free unused node and record

    destroy_node(new_node);
  }

  list_append(res_node->line_numbers, new_line_number);
}

static bool number_list_comparator(void *a, void *b) {
  return *(uint64_t *)list_peek((list_t *)a) <
         *(uint64_t *)list_peek((list_t *)b);
}

static void *mapping_func(void *element) {
  return ((tree_node_t *)element)->line_numbers;
}

void line_set_to_stdout(line_set_t *set) {
  dynamic_array_t *arr = splay_tree_map(set->tree, mapping_func);

  dynamic_array_t *sorted = sort_numbers(arr, number_list_comparator);
  destroy_dynamic_array(arr);

  size_t n = dynamic_array_get_size(sorted);

  uint64_t *number;

  for (size_t i = 0; i < n; i++) {
    while ((number = list_pop_front(dynamic_array_get(sorted, i))) != NULL) {
      printf("%lu ", *number);
      free(number);
    }
    printf("\n");
  }

  destroy_dynamic_array(sorted);
}