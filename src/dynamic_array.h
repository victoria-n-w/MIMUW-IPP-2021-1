#ifndef __DYNAMIC_ARAY_H
#define __DYNAMIC_ARAY_H

typedef struct dynamic_array dynamic_array_t;

dynamic_array_t *new_dynamic_array();

void destroy_dynamic_array(dynamic_array_t *arr);

#endif