#include "sort_lex.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"
#include "list.h"
#include "safe_funcs.h"

static const char FIRST_LETTER = 33;
static const size_t N_BUCKETS = 100;
/**
 * returns the lenght of the longest word. Sets values in length array
 *
 * words of lenght c are appended to list in words_of_lenght[c - 1]
 */
static size_t init_lenghts(dynamic_array_t *words, size_t n, size_t *length) {
  size_t longest = 0;

  for (size_t i = 0; i < n; i++) {
    length[i] = strlen((char *)dynamic_array_get(words, i));
    if (length[i] > longest) longest = length[i];
  }

  return longest;
}

static void spread_words_to_lists(dynamic_array_t *words, size_t n,
                                  list_t **lists, size_t *length) {
  for (size_t i = 0; i < n; i++) {
    list_append(lists[length[i] - 1], dynamic_array_get(words, i));
  }
}

static list_t *do_the_sorting(list_t **words_of_lenght, size_t longest) {
  list_t *res = new_list();

  // initializing buckets
  list_t **buckets = safe_malloc(sizeof(list_t *) * N_BUCKETS);
  for (size_t i = 0; i < N_BUCKETS; i++) buckets[i] = new_list();

  char *word;

  for (int c = longest - 1; c >= 0; c--) {
    res = list_concat(words_of_lenght[c], res, true);

    // spread to the buckets
    while ((word = list_pop_front(res)) != NULL) {
      list_append(buckets[word[c] - FIRST_LETTER], word);
    }

    // merge the buckets
    for (size_t i = 0; i < N_BUCKETS; i++) {
      res = list_concat(res, buckets[i], false);
    }
  }

  for (size_t i = 0; i < N_BUCKETS; i++) {
    destroy_list(buckets[i]);
  }

  free(buckets);

  return res;
}

dynamic_array_t *sort_lex(dynamic_array_t *arr) {
  size_t n = dynamic_array_get_size(arr);

  size_t *lenght = safe_malloc(sizeof(size_t) * n);
  size_t longest = 0;

  longest = init_lenghts(arr, n, lenght);

  list_t **words_of_lenght = safe_malloc(sizeof(list_t *) * longest);
  for (size_t i = 0; i < longest; i++) words_of_lenght[i] = new_list();

  spread_words_to_lists(arr, n, words_of_lenght, lenght);

  list_t *res_list = do_the_sorting(words_of_lenght, longest);

  free(lenght);
  free(words_of_lenght);
  return list_to_dynamic_array(res_list, n);
}