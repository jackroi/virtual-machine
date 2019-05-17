/**
 * vm-state.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Virtual machine state manager
*/


#include "vm-state.h"
#include "stack.h"


/**
 *
 * ? maybe the vm should have a struct state that each
 * ? functions that manipulate the state carry it around
 * ? so, the number of parameter of the functions would be
 * ? be reduced, and avoid global variables
 *
*/


static int regs[REGS_NUM] = { 0 };    /* ? probably should be initialized in init */
static stack_t stack;
static int *code;
static int ip, sp;       /* TODO maybe should be init */

/**/
int init() {
  int i;

  for (i = 0; i < REGS_NUM; i++) {
    regs[i] = 0;
  }

  stack = get_empty();


}
void get_registers(int *registers);
int get_register(int reg_code);
void set_register(int reg_code, int value);
int set_code(const int *_code);
void get_code(int **_code);
stack_t *get_stack();
int stack_push(int value);
int stack_pop(int *value);
int stack_isempty();
int get_ip(void);
void set_ip(int value);

/* ? probably not needed */
int get_sp();
void set_sp(int value);
