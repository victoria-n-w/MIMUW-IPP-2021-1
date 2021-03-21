#include "line_record.h"

#include <stdlib.h>

#include "safe_funcs.h"

line_record_t* new_line_record() {
  line_record_t* res = safe_malloc(sizeof(line_record_t));
  res->numbers = new_dynamic_array();
  res->words = new_dynamic_array();
  return res;
}

void destroy_line_record(line_record_t* rec) {
  if (rec == NULL) return;

  while (1) {
    long double* ptr = dynamic_array_pop(rec->numbers);
    if (ptr == NULL) break;
    free(ptr);
  }

  destroy_dynamic_array(rec->numbers);

  while (1) {
    char* word_ptr = dynamic_array_pop(rec->words);
    if (word_ptr == NULL) return;
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

void line_rec_sort(line_record_t* rec){};