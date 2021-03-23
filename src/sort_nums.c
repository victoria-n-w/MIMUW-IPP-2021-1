#include "sort_nums.h"

#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

static void heap_up(dynamic_array_t *arr, size_t i) {
  while (i > 1) {
    if (*(long double *)dynamic_array_get(arr, i / 2) <
        *(long double *)dynamic_array_get(arr, i)) {
      dynamic_array_swap(arr, i, i / 2);
      i /= 2;
    } else {
      break;
    }
  }
}

static void build_heap(dynamic_array_t *arr, dynamic_array_t *res, size_t n) {
  for (size_t heap_size = 1; heap_size <= n; heap_size++) {
    dynamic_array_set(res, heap_size, dynamic_array_get(arr, heap_size - 1));
    heap_up(res, heap_size);
  }
}

static void heap_down(dynamic_array_t *arr, size_t n) {
  size_t k = 1;
  while (1) {
    // if T[2*k + 1] > T[k]: swap(T[2*k+1], T[k])
    if (2 * k + 1 <= n && *(long double *)dynamic_array_get(arr, 2 * k + 1) >
                              *(long double *)dynamic_array_get(arr, k)) {
      dynamic_array_swap(arr, k, k * 2 + 1);
      k = k * 2 + 1;
    }  // if T[2*k] > T[k]: swap(T[2*k], T[k])
    else if (2 * k <= n && *(long double *)dynamic_array_get(arr, 2 * k) >
                               *(long double *)dynamic_array_get(arr, k)) {
      dynamic_array_swap(arr, k, 2 * k);
      k *= 2;
    } else {
      break;
    }
  }
}

static void sort_heap(dynamic_array_t *arr, size_t n) {
  for (size_t last_element = n; last_element > 1; last_element--) {
    dynamic_array_swap(arr, last_element, 1);
    heap_down(arr, last_element - 1);
  }
}

dynamic_array_t *sort_numbers(dynamic_array_t *arr) {
  size_t n = dynamic_array_get_size(arr);
  dynamic_array_t *res = new_dynamic_array_of_size(n + 1);
  dynamic_array_set(res, 0, NULL);

  build_heap(arr, res, n);

  sort_heap(res, n);

  dynamic_array_pop_front(res);

  return res;
}