#include "dynamic_array.h"

#include <stdlib.h>

#include "safe_funcs.h"

typedef struct dynamic_array {
  size_t size, alloced_size, min_size;
  void **arr;
} dynamic_array_t;

dynamic_array_t *new_dynamic_array(size_t init_size) {
  dynamic_array_t *res = safe_malloc(sizeof(dynamic_array_t));
  res->arr = safe_malloc(sizeof(void *) * init_size);
  res->alloced_size = res->min_size = init_size;
  res->size = 0;
  return res;
}

void destroy_dynamic_array(dynamic_array_t *arr) {
  if (arr == NULL) return;
  if (arr->arr != NULL) free(arr->arr);
  free(arr);
}

static void double_size(dynamic_array_t *arr) {
  void **new_arr =
      (void **)safe_realloc(arr->arr, sizeof(void *) * arr->alloced_size * 2);

  arr->arr = new_arr;
  arr->alloced_size *= 2;
}

static void halve_size(dynamic_array_t *arr) {
  void **new_arr =
      (void **)safe_realloc(arr->arr, sizeof(void *) * arr->alloced_size / 2);

  arr->arr = new_arr;
  arr->alloced_size /= 2;
}

void dynamic_array_push(dynamic_array_t *arr, void *element) {
  if (arr->size == arr->alloced_size) {
    double_size(arr);
  }

  arr->arr[arr->size++] = element;
}

void *dynamic_array_pop(dynamic_array_t *arr) {
  if (arr == NULL || arr->size == 0) return NULL;

  void *res = arr->arr[--arr->size];

  if (arr->size < arr->alloced_size / 2 && arr->size > arr->min_size) {
    halve_size(arr);
  }

  return res;
}

void *dynamic_array_get(dynamic_array_t *arr, size_t i) {
  if (arr == NULL || arr->size <= i) return NULL;
  return arr->arr[i];
}

size_t dynamic_array_get_size(dynamic_array_t *arr) { return arr->size; }