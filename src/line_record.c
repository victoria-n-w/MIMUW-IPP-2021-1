#include "line_record.h"

#include <stdio.h>
#include <stdlib.h>

#include "safe_funcs.h"
#include "sort_lex.h"
#include "sort_nums.h"

line_record_t* new_line_record() {
  line_record_t* res = safe_malloc(sizeof(line_record_t));
  res->numbers = new_dynamic_array(10);
  res->words = new_dynamic_array(10);
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