/**
 * vm-state.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Virtual machine state manager
*/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "vm-state.h"


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
void state_init(state_t *state) {
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

}

/* ? possible name change (shutdown) */
/* ? should be called after each error ? (probably it's already this way) */
void state_clean(state_t *state) {
  free(state->code);
  state->code = NULL;

  /* ? Warning if (sp != 0) ? (probably not) */
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

int stack_peek(state_t *state, int index, int *value) {
  if (state->sp > index) {
    *value = state->stack[state->sp - index - 1];
    return 1;
  } else {
    return 0;
  }
}

int get_ip(const state_t *state) {
  return state->ip;
}

int set_ip(state_t *state, int value) {
  if (value >= 0 && value < state->code_length) {
    state->ip = value;
    return 1;
  } else {
    return 0;
  }
}


/* TODO probably not needed, considering that sp is modified by push an pop */
int get_sp(const state_t *state) {
  return state->sp;
}

void set_sp(state_t *state, int value) {
  state->sp = value;
}


int *get_code(const state_t *state) {
  return state->code;
}

size_t get_code_length(const state_t *state) {
  return state->code_length;
}

int set_code(const int *_code);
/*stack_t *get_stack();*/
int stack_isempty();

/* ? probably not needed */
