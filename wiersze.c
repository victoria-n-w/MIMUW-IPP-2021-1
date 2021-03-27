#define _GNU_SOURCE

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"
#include "line_record.h"
#include "line_set.h"
#include "parsers.h"

bool is_whitespace(char x) {
  if (x == 32 || x == 9 || x == 11 || x == 12 || x == 13) return true;
  return false;
}

bool valid_character(char x) {
  if (33 <= x || x <= 126) return true;
  if (is_whitespace(x) || x == '\n') return true;
  return false;
}

bool valid_line(char *buffer) {
  size_t cnt = 0;
  while (buffer[cnt] != 0) {
    if (!valid_character(buffer[cnt++])) return false;
  }
  return true;
};

// processes line
static void process_data(char *buffer, line_set_t *lines_data,
                         uint64_t line_cnt) {
  if (!valid_line(buffer)) {
    fprintf(stderr, "ERROR %lu\n", line_cnt);
    return;
  }

  line_record_t *rec = new_line_record(line_cnt);

  size_t word_beggining = 0, word_end = 0;

  // parse until the end of the line
  while (buffer[word_end] != 0 && buffer[word_end] != '\n') {
    // parsing whitespaces
    while (is_whitespace(buffer[word_end])) {
      word_end++;
      word_beggining++;
    }

    // parsing valid word
    while (33 <= buffer[word_end] && buffer[word_end] <= 126) {
      word_end++;
    }

    if (word_beggining != word_end) {
      // the lenght of scanned word equals word_end - word_beggining
      size_t lenght = word_end - word_beggining;
      char *word = malloc(sizeof(char) * (lenght + 1));

      if (word == NULL) exit(1);

      size_t counter = 0;
      while (word_beggining != word_end) {
        word[counter++] = tolower(buffer[word_beggining++]);
      }
      // terminate word with NULL;
      word[counter] = 0;

      bool not_number = false;
      // TODO add word_lenght
      long double res = parse_number(word, lenght, &not_number);

      if (!not_number) {
        line_rec_insert_number(rec, res);
        free(word);
      } else {
        // set word to lowercase
        line_rec_insert_word(rec, word);
        // we dont free word* here,
        // because line record uses this memory
      }
    }
  }

  line_rec_commit(rec);

  // TODO this function has to free the rec memory
  line_set_insert(lines_data, rec);
}

int main() {
  uint64_t line_counter = 1;

  size_t BUFFER_SIZE = 256;
  char *buffer;
  buffer = malloc(sizeof(char) * BUFFER_SIZE);
  line_set_t *lines_data = new_line_set();

  while (getline(&buffer, &BUFFER_SIZE, stdin) != -1) {
    if (buffer[0] != '#') process_data(buffer, lines_data, line_counter);
    line_counter += 1;
  }

  line_set_to_stdout(lines_data);
  destroy_line_set(lines_data);
  free(buffer);
}