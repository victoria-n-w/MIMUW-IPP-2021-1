#include "parsers.h"

#include <errno.h>
#include <stdlib.h>

// TODO CHANGE BASE 0

static long double parse_long_double(const char *word, bool *not_number) {
  errno = 0;
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

static long double parse_regular_number(const char *word, bool *not_number,
                                        bool try_double) {
  char *endptr;

  long long res_ll = strtoll(word, &endptr, 10);

  // number was correctly parsed
  if (errno == 0 && *endptr == 0) {
    return res_ll;
  }
  errno = 0;
  unsigned long long res_ull = strtoull(word, &endptr, 10);

  // number was correctly parsed
  if (errno == 0 && *endptr == 0) {
    return res_ull;
  }

  if (try_double)
    return parse_long_double(word, not_number);
  else {
    *not_number = true;
    return 0;
  }
}

static bool is_hexadecimal(char *ptr, size_t lenght) {
  if (lenght < 2) return false;

  if (ptr[0] == '0' && ptr[1] == 'x') return true;
  return false;
}

static long double parse_base(const char *word, bool *not_number, int base) {
  char *endptr;
  unsigned long long res = strtoull(word, &endptr, base);
  if (errno == 0 && *endptr == 0) {
    return res;
  }
  errno = 0;

  if (base == 8) return parse_regular_number(word, not_number, true);

  return parse_regular_number(word, not_number, false);
  return 0;
}

long double parse_number(char *word, size_t lenght, bool *not_number) {
  errno = 0;
  if (lenght < 2) {
    return parse_regular_number(word, not_number, true);
  }

  if (word[0] == '0') {
    if (word[1] == 'x') {
      // "0x" is a correct number
      if (lenght == 2) return 0;

      return parse_base(word, not_number, 16);
    }

    if (word[1] == '.') {
      // "0." is the beginning of a long double number
      return parse_long_double(word, not_number);
    } else {
      // "0" is the beginning of an octadecimal numer
      return parse_base(word, not_number, 8);
    }
  }

  if (word[0] == '+') {
    if (is_hexadecimal(word + 1, lenght - 1)) {
      // +0x... is not a valid number
      *not_number = true;
      return 0;
    }
    return parse_regular_number(word, not_number, true);
  }

  if (word[0] == '-') {
    if (is_hexadecimal(word + 1, lenght - 1)) {
      // -0x... is not a valid number
      *not_number = true;
      return 0;
    }
  }

  return parse_regular_number(word, not_number, true);
  *not_number = true;
  return 0;
}