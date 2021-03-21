#include "line_set.h"

#include "line_record.h"
#include "safe_funcs.h"

typedef struct line_set {
  int foo;
} line_set_t;

line_set_t *new_line_set() { return safe_malloc(sizeof(line_set_t)); }

void destroy_line_set(line_set_t *set) {
  // TODO
  free(set);
}

void line_set_insert(line_set_t *set, line_record_t *rec) {
  // TODO
  destroy_line_record(rec);
}