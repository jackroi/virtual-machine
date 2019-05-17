/**
 * parser.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Machine code parser
*/


#include "exception-manager.h"
#include "parser.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


static int is_valid(const int *code);
static int get_code_length(FILE *f);
static int load_code(FILE *f, int *code, int c_length);


error_t parse_file(const char *filename, int **code, int *code_length) {
  FILE *f;
  int c_length;

  f = fopen(filename, "r");

  if (!f) {
    return CANNOT_OPEN_FILE;
  }

  c_length = get_code_length(f);

  if (!c_length) {
    return INVALID_CODE;
  }

  *code = (int *) malloc(sizeof(int) * c_length);

  if (!*code) {
    return MALLOC_ERROR;
  }

  load_code(f, *code, c_length);
  *code_length = c_length;

  /* TODO is_valid() */

  return 0;
}


static int is_valid(const int *code);

/**/
static int get_code_length(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  int c_length = 0;

  while ((nread = getline(&line, &len, f)) != EOF && !found) {
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

/**/
static int load_code(FILE *f, int *code, int c_length) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  int current_index = 0;

  while ((nread = getline(&line, &len, f)) != EOF) {
    int i, n;

    n = 0;
    for (i = 0; line[i] >= '0' && line[i] <= '9'; i++) {
      n = 10 * n + (line[i] - '0');
    }

    if (i > 0) {
      assert(current_index < c_length);     /* TODO throw error INVALID_CODE */
      code[current_index++] = n;
    }
  }

  free(line);

  return 1;         /* TODO implement return 0 (INVALID_CODE) */
}
