#ifndef _LINE_RECORD_H
#define _LINE_RECORD_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "dynamic_array.h"

typedef struct line_record line_record_t;

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

void line_rec_insert_number(line_record_t* rec, long double number);

/**
 * insert word into line rec
 * its lenght is specified by lenght parameter
 *
 * the numbers are not sorted
 */
void line_rec_insert_word(line_record_t* rec, char* word);

/**
 */
void line_rec_commit(line_record_t* rec);

/**
 * returns:
 *  -1 if a < b
 *   0 if a == b
 *   1 if a > b
 */
int line_rec_comparator(line_record_t* a, line_record_t* b);

uint64_t line_rec_get_number(line_record_t* rec);

#endif