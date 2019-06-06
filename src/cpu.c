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

/* TODO what should each func return ? */

static int DISPLAY(state_t *state, int params[]) {
  printf("%d\n", state->regs[params[0]]);     /* ? is it right to print \n ? */
  return 1;
}

/* print from sp - 1 to sp - n inclued */
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
  long int sum = ((long) (state->regs[params[0]])) + ((long) (state->regs[params[1]]));
  if (sum > INT_MAX || sum < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  } else {
    push(&state->stack, (int) sum);
    state->sp++; /* ? */
    return 1;
  }
}

static int SUB(state_t *state, int params[]) {
  long int sum = ((long) (state->regs[params[0]])) - ((long) (state->regs[params[1]]));
  if (sum > INT_MAX || sum < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  } else {
    push(&state->stack, (int) sum);
    state->sp++; /* ? */
    return 1;
  }
}

static int MUL(state_t *state, int params[]) {
  long int prod = ((long) (state->regs[params[0]])) * ((long) (state->regs[params[1]]));
  if (prod > INT_MAX || prod < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  } else {
    push(&state->stack, (int) prod);
    state->sp++; /* ? */
    return 1;
  }
}

static int DIV(state_t *state, int params[]) {
  if (state->regs[params[1]] == 0) {
    return 0;       /* TODO DIV_BY_ZERO */
  } else {
    int d = state->regs[params[0]] / state->regs[params[1]];
    push(&state->stack, d);
    state->sp++; /* ? */
    return 1;
  }
}

static int NOT_IMPL(state_t *state, int params[]) {
  return 0;       /* TODO NOT_IMPL */
}



static func_t instr_func[34] = {      /* TODO define 34 and declare const maybe */
  NOT_IMPL,
  DISPLAY,
  PRINT_STACK,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  PUSH,
  POP,
  MOV,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  CALL,
  RET,
  JMP,
  JZ,
  JPOS,
  JNEG,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  NOT_IMPL,
  ADD,
  SUB,
  MUL,
  DIV,
};


/* TODO maybe unify op_code and params[] into instruction[] */
int cpu_execute(state_t *state, int op_code, int params[]) {
  if (op_code > 33 || op_code < 0) {
    return 0;     /* TODO error */
  } else {
    return instr_func[op_code](state, params);
  }
}
