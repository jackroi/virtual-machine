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


static const char *instructions_name[34] = {    /* TODO define instr_number 34 */
  "HALT",
  "DISPLAY",
  "PRINT_STACK",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "PUSH",
  "POP",
  "MOV",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "CALL",
  "RET",
  "JMP",
  "JZ",
  "JPOS",
  "JNEG",
  "",
  "",
  "",
  "",
  "ADD",
  "SUB",
  "MUL",
  "DIV"
};

static int instructions_length[34] = {    /* TODO define instr_number 34 */
  1,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  1,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3
};


static int is_valid(const int *code, int c_length);
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
  if (!is_valid(*code, c_length)) {
    return INVALID_CODE;
  }

  return 0;
}

/* ? maybe it's not needed, maybe it's a duplicate */
/* it's interesting because it permits me to spot error soon */
static int is_valid(const int *code, int c_length) {
int i;
  int i_length;

  i = 0;
  while (i < c_length) {
    i_length = instructions_length[code[i]];      /* TODO instruction manager */

    if (code[i] < 0 || code[i] > 33 || instructions_name[code[i]][0] == '\0') {
      return 0;   /* TODO this is not structured programming */
    }

    i += i_length;
  }

  return 1;
}

/**/
static int get_code_length(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  int c_length = 0;

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

/* TODO handle input of negative numbers */
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

    /*
    trying to spot syntax errors (probably need a found variable into the previous for)
    TODO else if (line[i] != ';') (non è sufficiente)
    */
  }

  free(line);

  return 1;         /* TODO implement return 0 (INVALID_CODE) */
}
