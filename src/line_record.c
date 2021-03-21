#include "line_record.h"

#include <stdlib.h>

#include "safe_funcs.h"

line_record_t* new_line_record() {
  line_record_t* res = safe_malloc(sizeof(line_record_t));
}

void destroy_line_record(line_record_t* rec) {
  // TODO
  free(rec);
}

void line_rec_insert_number(line_record_t* rec, __float128 number){};

void line_rec_insert_word(line_record_t* rec, char* word){};

void line_rec_sort(line_record_t* rec){};