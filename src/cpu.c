/**
 * cpu.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Where the instructions are implemented
*/

#include "cpu.h"
#include "vm-state.h"
#include "stack.h"
#include <stdio.h>
#include <limits.h>

/*static int HALT()*/

/* TODO what should each funcs return ? */

static int DISPLAY(state_t *state, int params[]) {
  printf("%d\n", state->regs[params[0]]);     /* ? is it right to print \n ? */
  return 1;
}

static int PRINT_STACK(state_t *state, int params[]) {
  /* TODO */
}

static int PUSH(state_t *state, int params[]) {
  state->sp++; /* ? */
  return push(&state->stack, state->regs[params[0]]);        /* ? should i use stack_push or push ? */
}

static int POP(state_t *state, int params[]) {
  int res, value;
  state->sp--;
  res = pop(&state->stack, &value);

  state->regs[params[0]] = value;

  return res;
}

static int MOV(state_t *state, int params[]) {
  state->regs[params[0]] = params[1];
  return 1;
}

static int CALL(state_t *state, int params[]) {
  /* ? should i use cpu.PUSH and cpu.JMP or not */
  /* ? probabilmente no PUSH perchè alrimenti dovrei sporcare registri */
  /*PUSH(state, {...})*/
  int res;

  res = push(&state->stack, state->ip);
  state->sp++; /* ? */

  state->ip = params[0];

  return res;
}

static int RET(state_t *state, int params[]) {    /* ! params not used */
  int res, value;

  state->sp--;
  res = pop(&state->stack, &value);

  state->ip = value;

  return res;
}

static int JMP(state_t *state, int params[]) {
  /* todo assert ip < code_length (or something similar) (probably not with assert) */
  state->ip = params[0];

  return 1;

}

static int JZ(state_t *state, int params[]) {
  int value, res;
  res = pop(&state->stack, &value);

  if (!res) {
    return 0;     /* TODO error */
  } else if (value != 0) {
    state->ip = params[0];
    return 1;   /* ? */
  } else {
    return 1;
  }
}

static int JPOS(state_t *state, int params[]) {
  int value, res;
  res = pop(&state->stack, &value);

  if (!res) {
    return 0;     /* TODO error */
  } else if (value > 0) {
    state->ip = params[0];
    return 1;   /* ? */
  } else {
    return 1;
  }
}

static int JNEG(state_t *state, int params[]) {
  int value, res;
  res = pop(&state->stack, &value);

  if (!res) {
    return 0;     /* TODO error */
  } else if (value < 0) {
    state->ip = params[0];
    return 1;   /* ? */
  } else {
    return 1;
  }
}

static int ADD(state_t *state, int params[]) {
  if ((state->regs[params[0]] > 0) && (a > INT_MAX - x)) /* `a + x` would overflow */;
  if ((x < 0) && (a < INT_MIN - x)) /* `a + x` would underflow */;
}

static int SUB(state_t *state, int params[]) {

}

static int MUL(state_t *state, int params[]) {

}

static int DIV(state_t *state, int params[]) {

}

static int NOT_IMPL(state_t *state, int params[]) {

}



static func_t instr_func[34] = {

};      /* TODO define */


int cpu_execute(state_t *state, int op_code);

