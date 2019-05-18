/**
 * virtual-machine.c
 * Copyright © 2019 Giacomo Rosin
 *
 * The core of the project
*/

#include "virtual-machine.h"
#include "vm-state.h"
#include "stack.h"
#include "exception-manager.h"
#include "parser.h"
#include "cpu.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>



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


static void print_code(const int *code, int code_length);
static void execute_code(state_t *state);
static void execute_instruction(int instruction_code);
static void fetch(state_t *state, int *instruction, int *i_length);
static void execute(state_t *state, const int *instruction, int i_length);


/* ? should regs and stack be global variables */
/* ? IP and SP are included in the 32 registers ? */
/* ? maybe a ErrorManager that knows all the errors and exit */

/**/
error_t vm_run(int command, const char *filename) {
  error_t error;
  state_t state;
  state_init(&state);         /* ? where should it be implemented */


  error = parse_file(filename, &state.code, &state.code_length);

  if (error) {        /* ? forse non serve (a seconda di error management) */
    return error;
  }

  if (command == 1) {       /* todo define stampa 1 */
    print_code(state.code, state.code_length);
    free(state.code);
    state.code = NULL;
  } else {                  /* todo define esegui 2 */
    execute_code(&state);
    free(state.code);
    state.code = NULL;
  }

  return NO_ERROR;
}


/**
 * parse_file: parse the file and load the instructions into an array
 * return the error code if an error occurs, otherwise 0
 *
 * ? may throw alloc error or file not exist/found
*/
/* static int parse_file(const char *filename, int **code); */


/**/
static void print_code(const int *code, int code_length) {
  int i;
  int i_length;
  /*char *i_name;*/   /* ! defined inside while to avoid discading const qualifier */

  i = 0;
  printf("CODE LENGTH: %d\n", code_length);
  for (i = 0; i < code_length; i++) {
    printf("[%3d]\n", code[i]);
  }
  printf("\n\n");

  i = 0;
  while (i < code_length) {
    const char *i_name = instructions_name[code[i]];
    i_length = instructions_length[code[i]];      /* TODO instruction manager */

    if (i_length == 1) {
      printf("[%3d]\t%s\n", i, i_name);
    } else if (i_length == 2) {
      printf("[%3d]\t%s R%d\n", i, i_name, code[i+1]);
    } else if (i_length == 3) {
      if (code[i] == 12)              /* TODO i can do better and BUG (JMP, ...)*/    /* if is MOV */
        printf("[%3d]\t%s R%d %d\n", i, i_name, code[i+1], code[i+2]);
      else
        printf("[%3d]\t%s R%d R%d\n", i, i_name, code[i+1], code[i+2]);
    }

    i += i_length;
  }
}


/* ? what if execution error occurs (eg. div_by_zero) */
static void execute_code(state_t *state) {
  int instruction[3];       /* TODO define MAX_INSTR_LENGTH 3 */
  int i_length;
  while (state->code[state->ip] != 0) {
    fetch(state, instruction, &i_length);
    execute(state, instruction, i_length);
  }

  /* TODO possibile alternativa (facendo restituire a fetch l'op_code)
  while ((fetch(state, instruction, &i_length)) != 0) {
    execute(state, instruction, i_length);
  }
  */
}


/**/
static void fetch(state_t *state, int *instruction, int *i_length) {
  int i;
  int i_code = (state->code)[state->ip];

  *i_length = instructions_length[i_code];

  /* fill instruction vector with info */
  instruction[0] = i_code;
  for (i = 1; i < *i_length; i++) {
    instruction[i] = (state->code)[state->ip + i];
  }

  state->ip += *i_length;
}

/**/
static void execute(state_t *state, const int *instruction, int i_length) {   /* ? probably i_length not needed */
  /* TODO should return error, so i can stop execution if error */
  int params[2] = {instruction[1], instruction[2]};
  cpu_execute(state, instruction[0], params);
}
