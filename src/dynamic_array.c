#include "dynamic_array.h"

#include <stdio.h>
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

dynamic_array_t *new_dynamic_array_of_size(size_t size) {
  dynamic_array_t *res = new_dynamic_array(size);
  res->size = size;
  return res;
}

static void invalid_element(dynamic_array_t *arr, size_t i) {
  fprintf(stderr,
          "Cannot access element in array of size: %d; requested element: %d\n",
          arr->size, i);
  exit(1);
}

static void invalid_array() {
  fprintf(stderr, "Trying to read from NULL array\n");
  exit(1);
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
  if (arr == NULL) invalid_array();
  if (arr->size == 0) return NULL;

  void *res = arr->arr[--arr->size];

  if (arr->size < arr->alloced_size / 2 && arr->size > arr->min_size) {
    halve_size(arr);
  }

  return res;
}

void *dynamic_array_get(dynamic_array_t *arr, size_t i) {
  if (arr == NULL) invalid_array();
  if (arr->size <= i) invalid_element(arr, i);
  return arr->arr[i];
}

size_t dynamic_array_get_size(dynamic_array_t *arr) { return arr->size; }

void dynamic_array_set(dynamic_array_t *arr, size_t i, void *x) {
  if (arr == NULL) invalid_array();
  if (arr->size <= i) invalid_element(arr, i);
  arr->arr[i] = x;
}

void dynamic_array_swap(dynamic_array_t *arr, size_t i, size_t j) {
  if (arr == NULL) invalid_array();
  if (arr->size <= i) invalid_element(arr, i);
  if (arr->size <= j) invalid_element(arr, j);
  void *temp = arr->arr[i];
  arr->arr[i] = arr->arr[j];
  arr->arr[j] = temp;
}

void *dynamic_array_pop_front(dynamic_array_t *arr) {
  void *temp = arr->arr[0];
  for (size_t i = 0; i < arr->size - 1; i++) {
    arr->arr[i] = arr->arr[i + 1];
  }
  arr->arr[arr->size - 1] = temp;
  return dynamic_array_pop(arr);
}