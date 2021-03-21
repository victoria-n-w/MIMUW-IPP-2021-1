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

#endif