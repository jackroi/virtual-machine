/**
 * vm-state.h
 * Copyright © 2019 Giacomo Rosin
*/


#ifndef VM_STATE_H
#define VM_STATE_H


#define REGS_NUM 32

#include "stack.h"


struct state {
  int regs[REGS_NUM];
  int stack[STACK_SIZE];
  int *code;
  int code_length;
  int ip;
  int sp;     /* ? probably not needed */
};

typedef struct state state_t;


int state_init(state_t *state);
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


#endif
