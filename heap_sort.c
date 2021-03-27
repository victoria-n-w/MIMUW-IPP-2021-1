#include "heap_sort.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

static void heap_up(dynamic_array_t *arr, size_t i,
                    bool (*cmp)(void *, void *)) {
  while (i > 1) {
    // if T[i/2] < T[i]
    if (cmp(dynamic_array_get(arr, i / 2), dynamic_array_get(arr, i))) {
      dynamic_array_swap(arr, i, i / 2);
      i /= 2;
    } else {
      break;
    }
  }
}

static void build_heap(dynamic_array_t *arr, dynamic_array_t *res, size_t n,
                       bool (*cmp)(void *, void *)) {
  for (size_t heap_size = 1; heap_size <= n; heap_size++) {
    dynamic_array_set(res, heap_size, dynamic_array_get(arr, heap_size - 1));
    heap_up(res, heap_size, cmp);
  }
}

static void heap_down(dynamic_array_t *arr, size_t n,
                      bool (*cmp)(void *, void *)) {
  // largest is the index, at which the greatest of three compared elements is
  size_t largest, k = 1;

  while (1) {
    largest = k;
    // if T[2*k + 1] > T[k]: swap(T[2*k+1], T[k])
    if (2 * k + 1 <= n && cmp(dynamic_array_get(arr, largest),
                              dynamic_array_get(arr, 2 * k + 1))) {
      largest = 2 * k + 1;
    }  // if T[2*k] > T[k]: swap(T[2*k], T[k])
    if (2 * k <= n &&
        cmp(dynamic_array_get(arr, largest), dynamic_array_get(arr, 2 * k))) {
      largest = 2 * k;
    }

    if (largest != k) {
      dynamic_array_swap(arr, largest, k);
    } else {
      break;
    }
  }
}

static void sort_heap(dynamic_array_t *arr, size_t n,
                      bool (*cmp)(void *, void *)) {
  for (size_t last_element = n; last_element > 1; last_element--) {
    dynamic_array_swap(arr, last_element, 1);
    heap_down(arr, last_element - 1, cmp);
  }
}

dynamic_array_t *sort_numbers(dynamic_array_t *arr,
                              bool (*cmp)(void *, void *)) {
  size_t n = dynamic_array_get_size(arr);
  dynamic_array_t *res = new_dynamic_array_of_size(n + 1);
  dynamic_array_set(res, 0, NULL);

  build_heap(arr, res, n, cmp);

  sort_heap(res, n, cmp);

  dynamic_array_pop_front(res);

  return res;
}

bool ld_comparator(void *a, void *b) {
  return *(long double *)a < *(long double *)b;
}