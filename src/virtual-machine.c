/**
 * virtual-machine.c
 * Copyright © 2019 Giacomo Rosin
 *
 * The core of the virtual machine: starts the virtual machine,
 * parses the source code contained in the input file and executes the command received.
 * - 'print' / 'stampa': prints the source code of the input file
 * - 'run' / 'esegui': executes the code of the input file
*/


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "virtual-machine.h"
#include "exception-manager.h"
#include "instruction-set.h"
#include "vm-state.h"
#include "parser.h"
#include "cpu.h"


static void print_code(const int *code, size_t code_length);
static error_t execute_code(state_t *state);
static error_t fetch(state_t *state, int *instruction);
static error_t execute(state_t *state, const int *instruction);


/**
 * vm_run: initialise the virtual machine, parse the source code contained in the input file
 * and execute the command received
 * - command: 'print'/'stampa' or 'run'/'esegui'
 * - filename: source code path (file .cvm)
 * return an exit status to signal eventual errors
 */
error_t vm_run(command_t command, const char *filename) {
  error_t error;
  state_t state;
  state_init(&state);                                             /* initialise the state of the vm */

  error = parse_file(filename, &state.code, &state.code_length);  /* parse the file containing the source code and load the instructions */
  if (error) {                                                    /* catch error */
    state_clean(&state);                                          /* clean up vm state before shutdown */
    return error;                                                 /* return exit status */
  }

  if (command == PRINT) {
    print_code(state.code, state.code_length);                    /* print the program */
  } else {
    error = execute_code(&state);                                 /* execute the source code and catch eventual errors */
  }

  state_clean(&state);                                            /* clean up vm state before shutdown */

  return error;                                                   /* return exit status */
}

/**
 * print_code: print the source code
 * - code: array of integer, containing the machine code
 * - code_length: length of the array
 */
static void print_code(const int *code, size_t code_length) {
  unsigned int i;

  i = 0;
  while (i < code_length) {                             /* loop through the array */
    int i_code = code[i];                               /* get the instruction code */
    const char *i_fmt = get_format(i_code);             /* get the instruction format for printing */
    int i_length = get_instruction_length(i_code);      /* get the instruction length */

    /* print the instruction (and its parameters) basing on its length */
    if (i_length == 1) {
      printf(i_fmt, i);
    } else if (i_length == 2) {
      printf(i_fmt, i, code[i+1]);
    } else if (i_length == 3) {
      printf(i_fmt, i, code[i+1], code[i+2]);
    }

    i += i_length;                                      /* "jump" to the next instruction */
  }
}

/**
 * execute_code: execute the machine code by fetching and executing each instruction
 * - state: pointer to the state of the vm, that will be modified at each instruction
 * return an exit status to signal eventual errors
 */
static error_t execute_code(state_t *state) {
  int instruction[MAX_INSTR_LENGTH];
  error_t error;
  int ended;

  /* fetch and execute each instruction, modifing vm state accordingly */
  ended = 0;
  error = NO_ERROR;
  while (!ended && !error) {                    /* go through the machine code array, stop when instruction HALT (0) is found or an error occurred */
    error = fetch(state, instruction);          /* fetch the instruction by loading it in the instruction array and update the instruction pointer (ip) */
    if (!error) {                               /* if no errors has occurred */
      error = execute(state, instruction);      /* execute the instruction and update the vm state */
      ended = (instruction[0] == 0);            /* check if last instruction was HALT (0) */
    }
  }

  return error;                                 /* return exit status */
}

/**
 * fetch: fetch the next instruction (pointed by ip) from machine code array
 * - state: pointer to the state of the vm (contains ip, machine code array, ...)
 * return an exit status to signal eventual errors
 */
static error_t fetch(state_t *state, int *instruction) {
  int curr_ip, i_code, i_length;
  int i;

  if (!is_ip_valid(state)) return INVALID_IP;       /* check if instruction pointer is valid, otherwise return an error */

  curr_ip = get_ip(state);                          /* get the current instruction pointer */
  i_code = (state->code)[curr_ip];                  /* get the current instruction code */
  i_length = get_instruction_length(i_code);        /* get the current instruction length */

  /* fill instruction array with instruction code and parameters */
  instruction[0] = i_code;
  for (i = 1; i < i_length; i++) {
    instruction[i] = (state->code)[curr_ip + i];
  }

  set_ip(state, curr_ip + i_length);                /* update instruction pointer */

  return NO_ERROR;                                  /* no error, everything went fine */
}

/**
 * execute: execute the instruction and update the vm state accordingly
 * - state: pointer to the state of the vm (contains ip, sp, stack, regs, ...)
 * return an exit status to signal eventual errors
 */
static error_t execute(state_t *state, const int *instruction) {
  int params[2];

  /* fill params array with the instruction parameters */
  params[0] = instruction[1];
  params[1] = instruction[2];

  return cpu_execute(state, instruction[0], params);    /* make cpu execute the instruction */
}
