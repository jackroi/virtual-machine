/**
 * parser.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Machine code parser: parses the input file that contains the machine code
 * and loads it in an array. Moreover it makes a static validation of the source code
 * to spot eventual syntax errors.
*/


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stddef.h>
#include "parser.h"
#include "instruction-set.h"
#include "exception-manager.h"


static int is_valid(const int *code, int c_length);
static size_t get_code_length(FILE *f);
static int load_code(FILE *f, int *code, int c_length);

/**
 * parse_file: parse the input file and create an array with the machine code
 * - filename: source code path (file .cvm)
 * - code: pointer to the array that will be created and filled with machine code
 * - code_length: at the end of the functions it will contain the length of the newly created array
 * return an exit status to signal eventual errors
 */
error_t parse_file(const char *filename, int **code, size_t *code_length) {
  FILE *f;
  size_t c_length;
  int done;

  f = fopen(filename, "r");                               /* open input file */
  if (!f) return CANNOT_OPEN_FILE;                        /* catch error */

  c_length = get_code_length(f);                          /* get the length of the machine code */
  if (!c_length) return INVALID_CODE;                     /* catch error */

  *code = (int *) malloc(sizeof(int) * c_length);         /* allocate heap memory for the array */
  if (!*code) return MALLOC_ERROR;                        /* catch error */

  done = load_code(f, *code, c_length);                   /* load the machine code into the array */
  *code_length = c_length;                                /* set code_length accordingly */

  if (!done || !is_valid(*code, c_length)) {              /* catch error and check machine code validity */
    return INVALID_CODE;
  }

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * TODO maybe a better is_valid
 * is_valid: make a static validation of the source code to spot eventual syntax errors.
 * - code: array containing the machine code
 * - c_length: array length
 * return 1 if the code is valid, 0 otherwise
 */
static int is_valid(const int *code, int c_length) {
  const char *i_name;
  int i_code, i_length;
  int i, error;

  i = 0;
  error = 0;
  /* search for invalid instructions */
  while (i < c_length && !error) {                                /* loop through the array, stop in case of error */
    i_code = code[i];                                             /* get the instruction code */
    i_length = get_instruction_length(i_code);                    /* get the instruction length */
    i_name = get_instruction_name(i_code);                        /* get the instruction name */

    error = (i_code < 0 || i_code > 33 || i_name[0] == '\0');     /* look for possible error */

    i += i_length;                                                /* "jump" to the next instruction */
  }

  return !error;
}

/**
 * get_code_length: parse the input file to get the length of the machine code
 * - f: pointer to the input file
 * return the length of the machine code if found one, 0 otherwise
 */
static size_t get_code_length(FILE *f) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  size_t c_length = 0;

  /* search the first valid number in the file containing the machine code */
  while (!found && (nread = getline(&line, &len, f)) != EOF) {    /* read a line from the input file while a valid number is not found and the file isn't finished */
    int i;

    /* try to read a number that starts at the beginning of the line */
    c_length = 0;
    for (i = 0; line[i] >= '0' && line[i] <= '9'; i++) {          /* loop through the line characters, stop if a non-digit char is found */
      c_length = 10 * c_length + (line[i] - '0');
    }

    found = (i > 0);                                              /* if i > 0 the current number has at least a digit, hence it's valid */
  }

  free(line);                                                     /* deallocate the memory used by getline */

  return c_length;                                                /* return the length of the machine code */
}

/**
 * load_code: parse the input file to fill the array with machine instructions
 * - f: pointer to the input file
 * - code: array to fill
 * - c_length: array length
 * return 1 in case of success, 0 otherwise
 */
static int load_code(FILE *f, int *code, int c_length) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  int found = 0;
  int current_index = 0;
  int error = 0;

  /* read all the numbers representing pieces of instructions from the input file */
  while ((nread = getline(&line, &len, f)) != EOF && !error) {    /* loop through the input file, stop when EOF reached or error occurred */
    int i;
    long int n;
    int is_negative;                                              /* flag to signal if the number read is positive or negative */

    i = 0;
    is_negative = 0;
    if (line[i] == '-') {                                         /* if minus sign found */
      is_negative = 1;                                            /* the number is negative */
      i++;
    }

    /* try to read a number that starts at the beginning of the line */
    n = 0;
    for (; line[i] >= '0' && line[i] <= '9'; i++) {
      n = 10 * n + (line[i] - '0');
    }

    if (i > 1 || (i > 0 && !is_negative)) {                       /* if a valid number is found in the current line */
      /* ? eventually cast n to int */
      n = (is_negative) ? -n : n;                                 /* make it negative accordingly with the flag */

      if (n > INT_MAX || n < INT_MIN) {                           /* if the number isn't contained in the integer range */
        log_warning(INSTRUCTION_OVERFLOW);                        /* log a warning */
      }

      /* prevent accessing out of the array bounds (probably for incorrect code length declaration) */
      if (current_index < c_length) {
        code[current_index++] = n;                                /* write fetched number into machine code array */
      } else {
        error = 1;                                                /* error flag */
      }
    }

    /*
    trying to spot syntax errors (probably need a _found_ variable into the previous for)
    TODO else if (line[i] != ';') (non è sufficiente)
    */
  }

  free(line);                                                     /* deallocate the memory used by getline */

  return !error;
}
