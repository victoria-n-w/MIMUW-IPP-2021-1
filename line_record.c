#include "line_record.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap_sort.h"
#include "safe_funcs.h"
#include "sort_lex.h"

typedef struct line_record {
  uint64_t number;
  dynamic_array_t *words, *numbers;
} line_record_t;

line_record_t* new_line_record(int number) {
  line_record_t* res = safe_malloc(sizeof(line_record_t));
  res->numbers = new_dynamic_array(10);
  res->words = new_dynamic_array(10);
  res->number = number;
  return res;
}

void destroy_line_record(line_record_t* rec) {
  if (rec == NULL) return;

  // destroy rec->numbers
  while (1) {
    long double* ptr = dynamic_array_pop(rec->numbers);
    if (ptr == NULL) break;
    free(ptr);
  }

  destroy_dynamic_array(rec->numbers);

  // destroy rec->words
  while (1) {
    char* word_ptr = dynamic_array_pop(rec->words);
    if (word_ptr == NULL) break;
    free(word_ptr);
  }

  destroy_dynamic_array(rec->words);
  free(rec);
}

void line_rec_insert_number(line_record_t* rec, long double number) {
  long double* ptr = safe_malloc(sizeof(long double));
  *ptr = number;
  dynamic_array_push(rec->numbers, ptr);
};

void line_rec_insert_word(line_record_t* rec, char* word) {
  dynamic_array_push(rec->words, word);
};

static void rec_sort_numbers(line_record_t* rec) {
  dynamic_array_t* sorted = sort_numbers(rec->numbers, ld_comparator);
  destroy_dynamic_array(rec->numbers);
  rec->numbers = sorted;
}

static void rec_sort_words(line_record_t* rec) {
  dynamic_array_t* sorted = sort_lex(rec->words);
  destroy_dynamic_array(rec->words);
  rec->words = sorted;
}

void line_rec_commit(line_record_t* rec) {
  rec_sort_numbers(rec);
  rec_sort_words(rec);
}

uint64_t line_rec_get_number(line_record_t* rec) { return rec->number; }

int line_rec_comparator(line_record_t* a, line_record_t* b) {
  size_t a_size = dynamic_array_get_size(a->numbers);
  size_t b_size = dynamic_array_get_size(b->numbers);

  if (a_size < b_size) return -1;
  if (a_size > b_size) return 1;

  a_size = dynamic_array_get_size(a->words);
  b_size = dynamic_array_get_size(b->words);

  if (a_size < b_size) return -1;
  if (a_size > b_size) return 1;

  a_size = dynamic_array_get_size(a->numbers);

  long double a_num, b_num;

  for (size_t i = 0; i < a_size; ++i) {
    a_num = *(long double*)dynamic_array_get(a->numbers, i);
    b_num = *(long double*)dynamic_array_get(b->numbers, i);

    if (a_num < b_num) return -1;
    if (a_num > b_num) return 1;
  }

  a_size = dynamic_array_get_size(a->words);

  for (size_t i = 0; i < a_size; ++i) {
    int res =
        strcmp(dynamic_array_get(a->words, i), dynamic_array_get(b->words, i));

    if (res != 0) return res;
  }

  return 0;
}