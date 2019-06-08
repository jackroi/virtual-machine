/**
 * virtual-machine.c
 * Copyright © 2019 Giacomo Rosin
 *
 * The core of the project
*/

#include "virtual-machine.h"
#include "vm-state.h"
#include "exception-manager.h"
#include "parser.h"
#include "cpu.h"
#include "instruction-set.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



static void print_code(const int *code, size_t code_length);
static error_t execute_code(state_t *state);
static error_t execute_instruction(int instruction_code);
static error_t fetch(state_t *state, int *instruction, int *i_length);
static error_t execute(state_t *state, const int *instruction, int i_length);


/* ? should regs and stack be global variables */
/* ? IP and SP are included in the 32 registers ? */
/* ? maybe a ErrorManager that knows all the errors and exit */

/**/
error_t vm_run(int command, const char *filename) {
  error_t error;
  state_t state;
  state_init(&state);         /* ? where should it be implemented */


  error = parse_file(filename, &state.code, &state.code_length);
  if (error) return error;

  if (command == 1) {       /* todo define stampa 1 */
    /*print_code(get_code(&state), get_code_length(&state));*/      /* ? */
    print_code(state.code, state.code_length);      /* ? */
    state_clean(&state);
  } else {                  /* todo define esegui 2 */
    error = execute_code(&state);
    state_clean(&state);
  }

  return error;
}


/**
 * parse_file: parse the file and load the instructions into an array
 * return the error code if an error occurs, otherwise 0
 *
 * ? may throw alloc error or file not exist/found
*/
/* static int parse_file(const char *filename, int **code); */


/**/
static void print_code(const int *code, size_t code_length) {
  int i;

  /* TODO remove debug
  i = 0;
  printf("CODE LENGTH: %d\n", code_length);
  for (i = 0; i < code_length; i++) {
    printf("[%3d]\n", code[i]);
  }
  printf("\n\n");
  */

  i = 0;
  while (i < code_length) {
    const char *i_fmt = get_format(code[i]);
    int i_length = get_instrugtion_length(code[i]);

    if (i_length == 1) {
      printf(i_fmt, i);
    } else if (i_length == 2) {
      printf(i_fmt, i, code[i+1]);
    } else if (i_length == 3) {
      printf(i_fmt, i, code[i+1], code[i+2]);
    }

    i += i_length;
  }
}


/* ? what if execution error occurs (eg. div_by_zero) */
static error_t execute_code(state_t *state) {
  int instruction[3];       /* TODO define MAX_INSTR_LENGTH 3 */
  int i_length;
  error_t error;

  error = NO_ERROR;

  while (state->code[get_ip(state)] != 0 && !error) {       /* TODO avoid heap buffer overflow + get_ip() */
    error = fetch(state, instruction, &i_length);
    if (!error) {
      error = execute(state, instruction, i_length);
    }
  }

  return error;

  /* TODO possibile alternativa (facendo restituire a fetch l'op_code)
  while ((fetch(state, instruction, &i_length)) != 0 && !error) {
    execute(state, instruction, i_length);
  }
  */
}


/**/
static error_t fetch(state_t *state, int *instruction, int *i_length) {
  int i, res;
  int curr_ip = get_ip(state);
  int i_code = (state->code)[curr_ip];      /* TODO maybe get_code() */

  *i_length = get_instrugtion_length(i_code);

  /* fill instruction vector with info */
  instruction[0] = i_code;
  for (i = 1; i < *i_length; i++) {
    /* TODO check if it generates error when instruction is incomplete
    TODO (probably not because if instruction is incomplete fetch has already signaled the error) */
    instruction[i] = (state->code)[state->ip + i];    /* ? maybe a get_instruction() ? */
  }

  res = set_ip(state, curr_ip + *i_length);     /*state->ip += *i_length;*/
  if (!res) return INVALID_IP;

  return NO_ERROR;
}

/**/
static error_t execute(state_t *state, const int *instruction, int i_length) {   /* ? probably i_length not needed */
  /* TODO should return error, so i can stop execution if error */
  int params[2] = {instruction[1], instruction[2]};   /* TODO non ansi */
  /*
  params[0] = instruction[1];
  ...
  ? or maybe pass all the instructio as a unique array
  */
  /*printf(">>>\t%s\n", instructions_name[instruction[0]]); debug */
  return cpu_execute(state, instruction[0], params);
}
