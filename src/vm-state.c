/**
 * vm-state.c
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
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
  free(state->code);                              /* free allocated memory */
  state->code = NULL;
}

/**
 * get_register: get the value contained in the [reg_code] register
 * - state: pointer to vm state
 * - reg_code: number of the register to access
 * - *value: will contain the value read in the [reg_code] register
 * return 1 in case of success, 0 otherwise
 */
int get_register(const state_t *state, int reg_code, int *value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {         /* check reg_code validity */
    *value = state->regs[reg_code];                   /* copy register value into value */
    return 1;
  } else {
    return 0;                                         /* failed due to invalid reg_code */
  }
}

/**
 * set_register: set the [reg_code] register equal to value
 * - state: pointer to vm state
 * - reg_code: number of the register to access
 * - value: the value to write in the register
 * return 1 in case of success, 0 otherwise
 */
int set_register(state_t *state, int reg_code, int value) {
  if (reg_code >= 0 && reg_code < REGS_NUM) {     /* check reg_code validity */
    state->regs[reg_code] = value;                /* set register value */
    return 1;
  } else {
    return 0;                                     /* failed due to invalid reg_code */
  }
}

/**
 * stack_push: push a value into the stack
 * - state: pointer to vm state
 * - value: the value to push
 * return 1 in case of success, 0 otherwise
 */
int stack_push(state_t *state, int value) {
  if (state->sp < STACK_SIZE) {                 /* assert that stack isn't full */
    state->stack[state->sp++] = value;          /* insert value on top of the stack and increment stack pointer */
    return 1;
  } else {
    return 0;                                   /* signal stack overflow */
  }
}

/**
 * stack_pop: pop an item from the stack
 * - state: pointer to vm state
 * - *value: will contain the popped value
 * return 1 in case of success, 0 otherwise
 */
int stack_pop(state_t *state, int *value) {
  if (state->sp > 0) {                          /* assert that stack isn't empty */
    *value = state->stack[--(state->sp)];       /* remove element from the peak of the stack */
    return 1;
  } else {
    return 0;                                   /* signal stack overflow */
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
  if (state->sp > index) {                          /* check index validity */
    *value = state->stack[state->sp - index - 1];   /* get the value of the cell at index [sp - index - 1] */
    return 1;
  } else {
    return 0;                                       /* signal index not valid */
  }
}

/**
 * stack_isempty: check whether the stack is empty or not
 * - state: pointer to vm state
 * return 1 if the stack is empty, 0 otherwise
 */
int stack_isempty(state_t *state) {
  return state->sp == 0;                            /* stack pointer equals to 0 implies stack empty */
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
 */
void set_ip(state_t *state, int value) {
  state->ip = value;                                /* set a new instruction pointer value */
}

/**
 * is_ip_valid: check whether the instruction pointer has a valid value or not
 * - state: pointer to vm state
 * - value: the value with which set the ip
 * return 1 if ip is valid, 0 otherwise
 */
int is_ip_valid(state_t *state) {
  /* ip value must be greater or equal to zero and less than the length of the machine code array */
  return ((state->ip >= 0) && ((unsigned) state->ip < state->code_length));
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
 * return the length of the array containing the machine code
 */
size_t get_code_length(const state_t *state) {
  return state->code_length;
}
