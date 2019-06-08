/**
 * parser.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Machine code parser
*/


#include "exception-manager.h"
#include "parser.h"
#include "instruction-set.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>     /* TODO remove */
#include <limits.h>
#include <stddef.h>


static int is_valid(const int *code, int c_length);
static size_t get_code_length(FILE *f);
static int load_code(FILE *f, int *code, int c_length);


error_t parse_file(const char *filename, int **code, size_t *code_length) {
  FILE *f;
  size_t c_length;
  int error;

  f = fopen(filename, "r");

  if (!f) {     /* ? inline if */
    return CANNOT_OPEN_FILE;
  }

  c_length = get_code_length(f);

  if (!c_length) {     /* ? inline if */
    return INVALID_CODE;
  }

  *code = (int *) malloc(sizeof(int) * c_length);

  if (!*code) {     /* ? inline if */
    return MALLOC_ERROR;
  }

  error = load_code(f, *code, c_length);
  *code_length = c_length;

  /* TODO is_valid() */
  if (error || !is_valid(*code, c_length)) {     /* ? inline if */
    return INVALID_CODE;
  }

  return NO_ERROR;
}

/* ? maybe it's not needed, maybe it's a duplicate */
/* it's interesting because it permits me to spot error soon */
static int is_valid(const int *code, int c_length) {
  const char *i_name;
  int i_length;
  int i, error;

  i = 0;
  error = 0;
  while (i < c_length && !error) {
    i_length = get_instrugtion_length(code[i]);
    i_name = get_instruction_name(code[i]);

    error = (code[i] < 0 || code[i] > 33 || i_name[0] == '\0');

    i += i_length;
  }

  return !error;
}

/**/
static size_t get_code_length(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  size_t c_length = 0;

  while (!found && (nread = getline(&line, &len, f)) != EOF) {
    int i;

    c_length = 0;
    for (i = 0; line[i] >= '0' && line[i] <= '9'; i++) {
      c_length = 10 * c_length + (line[i] - '0');
    }

    found = (i > 0);
  }

  free(line);

  return c_length;
}


static int load_code(FILE *f, int *code, int c_length) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  int current_index = 0;
  int error = 0;


  while ((nread = getline(&line, &len, f)) != EOF && !error) {
    int i;
    long int n;
    int is_negative;

    i = 0;
    is_negative = 0;
    if (line[i] == '-') {
      is_negative = 1;
      i++;
    }

    n = 0;
    for (; line[i] >= '0' && line[i] <= '9'; i++) {
      n = 10 * n + (line[i] - '0');
    }

    if (i > 1 || (i > 0 && !is_negative)) {     /* TODO check if is correct */
      assert(current_index < c_length);     /* TODO throw error INVALID_CODE */

      n = (is_negative) ? -n : n;   /* ? eventually cast n to int */

      if (n > INT_MAX || n < INT_MIN) {
        log_warning(INSTRUCTION_OVERFLOW);
      }

      if (current_index < c_length) {
        code[current_index++] = n;
      } else {
        error = 1;
      }
    }

    /*
    trying to spot syntax errors (probably need a found variable into the previous for)
    TODO else if (line[i] != ';') (non è sufficiente)
    */
  }

  free(line);

  return error;         /* TODO implement return 0 (INVALID_CODE) */
}
