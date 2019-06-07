/**
 * vm-state.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Virtual machine state manager
*/

#include <stdlib.h>
#include <stdio.h>
#include "vm-state.h"
#include "stack.h"
#define STACK_SIZE 16000


/**
 *
 * ? maybe the vm should have a struct state that each
 * ? functions that manipulate the state carry it around
 * ? so, the number of parameter of the functions would be
 * ? be reduced, and avoid global variables
 *
*/

/* never used */
static int regs[REGS_NUM] = { 0 };    /* ? probably should be initialized in init */ /* TODO probably the regs shouldn't be initialised */
static int stack[STACK_SIZE];
static int *code;
static int ip, sp;       /* TODO maybe should be init */
/**/


/* ? is still necessary ? */
int state_init(state_t *state) {
  int i;

/* TODO probably the regs shouldn't be initialised
  for (i = 0; i < REGS_NUM; i++) {
    state->regs[i] = 0;
  }
*/

/* TODO probably stack shouldn't be initialised
  for (i = 0; i < STACK_SIZE; i++) {
    state->stack[i] = 0;
  }
*/

  state->ip = 0;
  state->sp = 0;
  state->code = NULL;

  return 1;
}


int get_register(const state_t *state, int reg_code, int *value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {
    *value = state->regs[reg_code];
    return 1;
  } else {
    return 0;
  }
}

int set_register(state_t *state, int reg_code, int value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {
    state->regs[reg_code] = value;
    return 1;
  } else {
    return 0;
  }
}

int stack_push(state_t *state, int value) {
  if (state->sp < STACK_SIZE) {
    state->stack[state->sp++] = value;
    return 1;
  } else {
    return 0;
  }
}

int stack_pop(state_t *state, int *value) {
  if (state->sp > 0) {
    *value = state->stack[--(state->sp)];
    return 1;
  } else {
    return 0;
  }
}

int get_ip(const state_t *state) {
  return state->ip;
}

void set_ip(state_t *state, int value) {
  /* ? maybe should check if ip is valid */
  state->ip = value;
}


/* TODO probably not needed, considering that sp is modified by push an pop */
int get_sp(const state_t *state) {
  return state->sp;
}

void set_sp(state_t *state, int value) {
  state->sp = value;
}


int set_code(const int *_code);
void get_code(int **_code);
/*stack_t *get_stack();*/
int stack_isempty();

/* ? probably not needed */
