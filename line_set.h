#ifndef _LINE_SET_H
#define _LINE_SET_H

#include "line_record.h"

typedef struct line_set line_set_t;

line_set_t *new_line_set();

/**
 * inserts a record into set
 * exits the program with signal 1 if any malloc fails
 */
void line_set_insert(line_set_t *set, line_record_t *rec);

/**
 * destroys the set, deallocating its contents
 */
void destroy_line_set(line_set_t *set);

/**
 * prints groups of similar lines in the set
 * takes O(nlogn) time to complete
 *
 * destroys inner set data in the process,
 * though destroy_line_set is required to be called afterwards
 * to avoid memory leaks
 */
void line_set_to_stdout(line_set_t *set);

#endif