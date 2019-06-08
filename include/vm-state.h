/**
 * vm-state.h
 * Copyright © 2019 Giacomo Rosin
*/


#ifndef VM_STATE_H
#define VM_STATE_H


#define REGS_NUM 32

#define STACK_SIZE 16000      /* TODO shared */



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
int state_clean(state_t *state);

int get_register(const state_t *state, int reg_code, int *value);
int set_register(state_t *state, int reg_code, int value);
int stack_push(state_t *state, int value);
int stack_pop(state_t *state, int *value);
int stack_peek(state_t *state, int index, int *value);
int get_ip(const state_t *state);
void set_ip(state_t *state, int value);


int *get_code(const state_t *state);
int get_code_length(const state_t *state);



/*
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


int get_sp();
void set_sp(int value);
*/

#endif
