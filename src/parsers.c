#include "parsers.h"

#include <errno.h>
#include <stdlib.h>

// TODO delete
#include <stdio.h>

static long double parse_long_double(const char *word, bool *not_number) {
  char *endptr;
  long double res_ld = strtold(word, &endptr);

  // number was correctly parsed
  if (errno == 0 && *endptr == 0) {
    return res_ld;
  }

  // word is not a number
  *not_number = true;
  return 0;
}

static long double parse_regular_number(const char *word, bool *not_number) {
  char *endptr;

  long long res_ll = strtoll(word, &endptr, 10);

  // number was correctly parsed
  if (errno == 0 && *endptr == 0) {
    return res_ll;
  }

  unsigned long long res_ull = strtoull(word, &endptr, 10);

  // number was correctly parsed
  if (errno == 0 && *endptr == 0) {
    return res_ull;
  }

  return parse_long_double(word, not_number);
}

static long double parse_base(const char *word, bool *not_number, int base) {
  char *endptr;
  unsigned long long res = strtoull(word, &endptr, base);
  if (errno == 0 && *endptr == 0) {
    return res;
  }
  *not_number = true;
  return 0;
}

long double parse_number(char *word, size_t lenght, bool *not_number) {
  errno = 0;
  if (lenght < 2) {
    return parse_regular_number(word, not_number);
  }

  char *end_character;

  unsigned long long res;

  if (word[0] == '0') {
    if (word[1] == 'x') {
      if (lenght == 2) {
        // "0x" is not a correct number
        *not_number = true;
        return 0;
      }
      return parse_base(word, not_number, 16);

    } else if (word[1] == '.') {
      // "0." is the beginning of a long double number
      return parse_long_double(word, not_number);
    } else {
      // "0" is the beginning of an octadecimal numer
      return parse_base(word, not_number, 8);
    }
  } else {
    return parse_regular_number(word, not_number);
  }

  *not_number = true;
  return 0;
}