#ifndef _PARSERS_H
#define _PARSERS_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * parses word and returns its value
 * the number can be unsigned long long, long long or long double
 *
 * sets the value of not_number to true, if the parsed string
 * wasn't number
 */
__float128 parse_number(char *word, size_t lenght, bool *not_number);

#endif