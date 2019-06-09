/**
 * vm-state.h
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
*/

#ifndef VM_STATE_H
#define VM_STATE_H


#include <stddef.h>
#define REGS_NUM 32
#define STACK_SIZE 16384


/* define state_t type, that represents the virtual machine state */
struct state {
  int regs[REGS_NUM];
  int stack[STACK_SIZE];
  int *code;
  size_t code_length;
  int ip;
  int sp;     /* ? probably not needed */
};

typedef struct state state_t;


void state_init(state_t *state);
void state_clean(state_t *state);
int get_register(const state_t *state, int reg_code, int *value);
int set_register(state_t *state, int reg_code, int value);
int stack_push(state_t *state, int value);
int stack_pop(state_t *state, int *value);
int stack_peek(state_t *state, int index, int *value);
int get_ip(const state_t *state);
void set_ip(state_t *state, int value);
int is_ip_valid(state_t *state);
int *get_code(const state_t *state);
size_t get_code_length(const state_t *state);


#endif
