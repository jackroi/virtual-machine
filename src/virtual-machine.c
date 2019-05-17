/**
 * virtual-machine.c
 * Copyright © 2019 Giacomo Rosin
 *
 * The core of the project
*/

#include <stdlib.h>
#include "virtual-machine.h"
#include "vm-state.h"
#include "stack.h"


static const char *instructions_name[16] = {    /* TODO define instr_number 16 */
  "HALT",
  "DISPLAY",
  "PRINT_STACK",
  "PUSH",
  "POP",
  "MOV",
  "CALL",
  "RET",
  "JMP",
  "JZ",
  "JPOS",
  "JNEG",
  "ADD",
  "SUB",
  "MUL",
  "DIV"
};

static int instructions_length[16] = {    /* TODO define instr_number 16 */
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  1,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3
};


static int parse_file(const char *filename, int **code);
static void print_code(const int *code);
static void execute_code(const int *code);
static void execute_instruction(int instruction_code);
static void fetch(int *instruction, int *i_length);
static void execute(const int *instruction, int i_length);


/* ? should regs and stack be global variables */
/* ? IP and SP are included in the 32 registers ? */
/* ? maybe a ErrorManager that knows all the errors and exit */

/**/
int vm_run(int command, const char *filename) {
  int error;
  int regs[REGS_NUM] = { 0 };       /* initialise regs to 0 */
  stack_t stack = get_empty();
  int *code;
  int ip, sp;         /* ? where should i keep the stack pointer, here or on the struct ? */

  init();


  error = parse_file(filename, &code);

  if (error) {        /* ? forse non serve (a seconda di error management) */
    return error;
  }

  if (command == 0) {       /* todo define stampa 0 */
    print_code(code);
    free(code);
    code = NULL;
  } else {                  /* todo define esegui 1 */
    execute_code(code);
    free(code);
    code = NULL;
  }

  return 0;
}

/**
 * parse_file: parse the file and load the instructions into an array
 * return the error code if an error occurs, otherwise 0
 *
 * ? may throw alloc error or file not exist/found
*/
static int parse_file(const char *filename, int **code);



static void print_code(const int *code);


/* ? what if execution error occurs (eg. div_by_zero) */
static void execute_code(const int *code, int *ip) {
  int instruction[3];       /* TODO define MAX_INSTR_LENGTH 3 */
  int i_length;
  while (code[*ip] != 0) {
    fetch(instruction, &i_length, ip);
    execute(instruction, i_length);
  }
}


/**/
static void fetch(int *instruction, int *i_length, int *ip) {

}

/**/
static void execute(const int *instruction, int i_length);
