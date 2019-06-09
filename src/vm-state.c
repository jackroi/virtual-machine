/**
 * vm-state.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Virtual machine state manager: provides functions to manipulate the virtual machine state.
 * The state is composed by:
 * - regs[]: array that represent the vm registers (32)
 * - stack[]: array that represent the vm stack (16 KiB)
 * - sp: stack pointer
 * - ip: instruction pointer
 * - code: pointer to the array containing the machine code
 * - code_length: length of the array
*/

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "vm-state.h"


/**
 * TODO check this comment
 * ? maybe the vm should have a struct state that each
 * ? functions that manipulate the state carry it around
 * ? so, the number of parameter of the functions would be
 * ? be reduced, and avoid global variables
 *
*/

/**
 * state_init: intialise the state of the vm
 * NB: registers and stack are not initialised, hence they will contains garbage
 * - state: pointer to vm state
 */
void state_init(state_t *state) {
  state->ip = 0;
  state->sp = 0;
  state->code = NULL;
}

/**
 * state_clean: clean up the vm state, freeing the allocated memory
 */
void state_clean(state_t *state) {
  free(state->code);
  state->code = NULL;
  /* ? Warning if (sp != 0) ? (probably not) */
}

/**
 * get_register: get the value contained in the [reg_code] register
 * - state: pointer to vm state
 * - reg_code: number of the register to access
 * - *value: will contain the value read in the [reg_code] register
 * return 1 in case of success, 0 otherwise
 */
int get_register(const state_t *state, int reg_code, int *value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {
    *value = state->regs[reg_code];
    return 1;
  } else {
    return 0;
  }
}

/**
 * set_register: set the value contained in the [reg_code] register
 * - state: pointer to vm state
 * - reg_code: number of the register to access
 * - value: the value to write in the register
 * return 1 in case of success, 0 otherwise
 */
int set_register(state_t *state, int reg_code, int value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {
    state->regs[reg_code] = value;
    return 1;
  } else {
    return 0;
  }
}

/**
 * stack_push: push a value into the stack
 * - state: pointer to vm state
 * - value: the value to push
 * return 1 in case of success, 0 otherwise
 */
int stack_push(state_t *state, int value) {
  if (state->sp < STACK_SIZE) {
    state->stack[state->sp++] = value;
    return 1;
  } else {
    return 0;
  }
}

/**
 * stack_pop: pop an item from the stack
 * - state: pointer to vm state
 * - *value: will contain the popped value
 * return 1 in case of success, 0 otherwise
 */
int stack_pop(state_t *state, int *value) {
  if (state->sp > 0) {
    *value = state->stack[--(state->sp)];
    return 1;
  } else {
    return 0;
  }
}

/**
 * stack_peek: peek a cell of the stack
 * - state: pointer to vm state
 * - index: index of the cell to peek (starting from the peak of the stack)
 * - *value: will contain the peeked value
 * return 1 in case of success, 0 otherwise
 */
int stack_peek(state_t *state, int index, int *value) {
  if (state->sp > index) {
    *value = state->stack[state->sp - index - 1];
    return 1;
  } else {
    return 0;
  }
}

/**
 * stack_isempty: check whether the stack is empty or not
 * - state: pointer to vm state
 * return 1 if the stack is empty, 0 otherwise
 */
int stack_isempty(state_t *state) {
  return state->sp == 0;
}

/**
 * get_ip: get the value of the instruction pointer
 * - state: pointer to vm state
 * return the value of the instruction pointer
 */
int get_ip(const state_t *state) {
  return state->ip;
}

/**
 * set_ip: set the value of the instruction pointer
 * - state: pointer to vm state
 * - value: the value with which set the ip
 * return 1 in case of success, 0 otherwise
 */
int set_ip(state_t *state, int value) {
  if (value >= 0 && value < state->code_length) {
    state->ip = value;
    return 1;
  } else {
    return 0;
  }
}

/**
 * get_sp: get the value of the stack pointer
 * - state: pointer to vm state
 * return the value of the stack pointer
 */
int get_sp(const state_t *state) {
  return state->sp;
}

/**
 * get_code: get the pointer to the array containing the machine code
 * - state: pointer to vm state
 * return the pointer to the array containing the machine code
 */
int *get_code(const state_t *state) {
  return state->code;
}

/**
 * get_code_length: get the length of the array containing the machine code
 * - state: pointer to vm state
 * return the ength of the array containing the machine code
 */
size_t get_code_length(const state_t *state) {
  return state->code_length;
}

/* TODO check if all prototypes are declare in header file */
