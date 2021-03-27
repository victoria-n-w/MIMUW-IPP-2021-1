#include "splay_tree.h"

#include <stdbool.h>
#include <stdlib.h>

#include "safe_funcs.h"

typedef struct node node_t;

struct node {
  node_t *left, *right, *father;
  void *element;
};

struct splay_tree {
  int (*cmp)(void *, void *);
  node_t *root;
};

static node_t *new_node(void *element, node_t *father) {
  node_t *res = safe_malloc(sizeof(node_t));
  res->left = res->right = NULL;
  res->element = element;
  res->father = father;
  return res;
}

splay_tree_t *new_splay_tree(int (*cmp)(void *, void *)) {
  splay_tree_t *res = safe_malloc(sizeof(splay_tree_t));
  res->cmp = cmp;
  res->root = NULL;
  return res;
}

static void destroy_nodes(splay_tree_t *tree, void (*destroy_node)(void *)) {
  dynamic_array_t *stack = new_dynamic_array(10);

  dynamic_array_push(stack, tree->root);

  node_t *node;

  while ((node = dynamic_array_pop(stack)) != NULL) {
    if (node->left) dynamic_array_push(stack, node->left);
    if (node->right) dynamic_array_push(stack, node->right);
    destroy_node(node->element);
    free(node);
  }
  destroy_dynamic_array(stack);
}

void destroy_splay_tree(splay_tree_t *tree, void (*destroy_node)(void *)) {
  if (tree == NULL) return;

  if (tree->root != NULL) {
    destroy_nodes(tree, destroy_node);
  }

  free(tree);
}

dynamic_array_t *splay_tree_map(splay_tree_t *tree, void *(*func)(void *)) {
  dynamic_array_t *res = new_dynamic_array(10);
  if (tree->root == NULL) return res;

  dynamic_array_t *stack = new_dynamic_array(10);
  dynamic_array_push(stack, tree->root);

  node_t *node;

  while (node = dynamic_array_pop(stack)) {
    dynamic_array_push(res, func(node->element));
    if (node->left) dynamic_array_push(stack, node->left);
    if (node->right) dynamic_array_push(stack, node->right);
  }

  destroy_dynamic_array(stack);

  return res;
}

static node_t *search_and_insert(splay_tree_t *tree, void *element) {
  node_t *curr = tree->root;

  while (1) {
    int compare_result = tree->cmp(curr->element, element);

    // element is greater thatn current
    // go to the right son
    if (compare_result < 0) {
      if (curr->right == NULL) {
        curr->right = new_node(element, curr);
        return curr->right;
      } else {
        curr = curr->right;
      }
    }
    // element is lesser than current
    // got to the left son
    else if (compare_result > 0) {
      if (curr->left == NULL) {
        curr->left = new_node(element, curr);
        return curr->left;
      } else {
        curr = curr->left;
      }
    }
    // element is equalt to the current one
    else {
      return curr;
    }
  }
}

static void rotate_right(node_t *x) {
  node_t *y = x->father;
  y->left = x->right;
  x->right = y;
  x->father = y->father;
  y->father = x;
}

static void rotate_left(node_t *x) {
  node_t *y = x->father;
  y->right = x->left;
  x->left = y;

  x->father = y->father;
  y->father = x;
}

/**
 * returns the new root
 */
static node_t *splay(node_t *node) {
  while (node->father != NULL) {
    if (node->father->father == NULL) {
      // we are the root's son
      if (node == node->father->left) {
        rotate_right(node);
      } else
        rotate_left(node);
    } else {
      if (node == node->father->left) {
        if (node->father == node->father->father->left) {
          // we are the left son of a left son
          rotate_right(node->father);
          rotate_right(node);
        } else {
          // we are left son of the right son
          rotate_right(node);
          rotate_left(node);
        }
      } else {
        if (node->father == node->father->father->right) {
          // we are the right son of a rifht son
          rotate_left(node->father);
          rotate_left(node);
        } else {
          rotate_left(node);
          rotate_right(node);
        }
      }
    }
  }
  return node;
}

void *splay_tree_insert(splay_tree_t *tree, void *element) {
  if (tree->root == NULL) {
    tree->root = new_node(element, NULL);
    return tree->root->element;
  }
  node_t *found = search_and_insert(tree, element);
  tree->root = splay(found);
  return found->element;
}
