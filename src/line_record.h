#ifndef _LINE_RECORD_H
#define _LINE_RECORD_H

#include <stdlib.h>

#include "dynamic_array.h"

typedef struct line_record {
  u_int64_t number;
  dynamic_array_t *words, *numbers;
} line_record_t;

/**
 * allocates memory for new line_record
 * returns pointer to this memory
 * exit(1) if malloc failed
 */
line_record_t* new_line_record();

/**
 * safely destroys line_record
 */
void destroy_line_record(line_record_t* rec);

void line_rec_insert_number(line_record_t* rec, __float128 number);

void line_rec_insert_word(line_record_t* rec, char* word);

void line_rec_sort(line_record_t* rec);

#endif