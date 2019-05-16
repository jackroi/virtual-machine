/**
 * virtual-machine.c
 * Copyright © 2019 Giacomo Rosin
 *
 * The core of the project
*/

#include <stdlib.h>
#include "virtual-machine.h"
#include "stack.h"


static int parse_file(const char *filename, int **instructions);
static void print_code(const int *instructions);
static void execute_code(const int *instructions);


/* ? should regs and stack be global variables */
/* ? IP and SP are included in the 32 registers ? */
/* ? maybe a ErrorManager that knows all the errors and exit */

/**/
int vm_run(int command, const char *filename) {
  int error;
  int regs[REGS_NUM] = { 0 };       /* initialise regs to 0 */
  stack_t stack = get_empty();
  int *instructions;
  int ip, sp;         /* ? where should i keep the stack pointer, here or on the struct ? */

  error = parse_file(filename, &instructions);

  if (error) {        /* ? forse non serve (a seconda di error management) */
    return error;
  }

  if (command == 0) {       /* todo define stampa 0 */
    print_code(instructions);
    free(instructions);
    instructions = NULL;
  } else {                  /* todo define esegui 1 */
    execute_code(instructions);
    free(instructions);
    instructions = NULL;
  }

  return 0;
}

/**
 * parse_file: parse the file and load the instructions into an array
 * return the error code if an error occurs, otherwise 0
 *
 * ? may throw alloc error or file not exist/found
*/
static int parse_file(const char *filename, int **instructions);



static void print_code(const int *instructions);


/* ? what if execution error occurs (eg. div_by_zero) */
static void execute_code(const int *instructions);
