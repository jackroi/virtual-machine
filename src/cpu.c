/**
 * cpu.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Where the instructions are implemented
*/

#include "cpu.h"
#include "vm-state.h"
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
  int value, res;
  res = get_register(state, params[0], &value);
  if (!res) {
    return 0; /* TODO REG_NOT_EXIST */
  }
  res = stack_push(state, value);

  return res; /* TODO STACK_OVERFLOW */
}

static int POP(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) {
    return 0; /* TODO STACK_UNDERFLOW */
  }

  res = set_register(state, params[0], value);

  return res;   /* TODO REG_NOT_EXIST */
}

static int MOV(state_t *state, int params[]) {
  return set_register(state, params[0], params[1]);
}

static int CALL(state_t *state, int params[]) {
  int res;

  res = stack_push(state, get_ip(state));

  if (!res) {
    return 0; /* TODO STACK_OVERFLOW */
  }

  set_ip(state, params[0]);

  return 1;   /* TODO OK (NO_ERROR) */
}

static int RET(state_t *state, int params[]) {    /* ! params not used */
  int value, res;

  res = stack_pop(state, &value);
  if (!res) {   /* ? maybe inline if */
    return 0;   /* TODO STACK_UNDERFLOW */
  }

  set_ip(state, value);

  return 1;   /* TODO OK (NO_ERROR) */
}

static int JMP(state_t *state, int params[]) {
  /* todo assert ip < code_length (or something similar) (probably not with assert) */
  set_ip(state, params[0]);

  return 1;
}

static int JZ(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) {   /* ? maybe inline if */
    return 0;   /* TODO STACK_UNDERFLOW */
  }

  if (value != 0) {
    set_ip(state, params[0]);
  }

  return 1;   /* TODO OK (NO_ERROR) */
}

static int JPOS(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) {   /* ? maybe inline if */
    return 0;   /* TODO STACK_UNDERFLOW */
  }

  if (value > 0) {
    set_ip(state, params[0]);
  }

  return 1;   /* TODO OK (NO_ERROR) */
}

static int JNEG(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) {   /* ? maybe inline if */
    return 0;   /* TODO STACK_UNDERFLOW */
  }

  if (value < 0) {
    set_ip(state, params[0]);
  }

  return 1;   /* TODO OK (NO_ERROR) */
}

static int ADD(state_t *state, int params[]) {
  int p1, p2, res;
  long int sum;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) {
    return 0;     /* TODO REG_NOT_EXIST */
  }

  sum = ((long) p1) + ((long) p2);
  if (sum > INT_MAX || sum < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  }

  res = stack_push(state, (int) sum);
  if (!res) {
    return 0;   /* TODO STACK_OVERFLOW */
  }

  return 1;
}

static int SUB(state_t *state, int params[]) {
  int p1, p2, res;
  long int diff;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) {
    return 0;     /* TODO REG_NOT_EXIST */
  }

  diff = ((long) p1) - ((long) p2);
  if (diff > INT_MAX || diff < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  }

  res = stack_push(state, (int) diff);
  if (!res) {
    return 0;   /* TODO STACK_OVERFLOW */
  }

  return 1;
}

static int MUL(state_t *state, int params[]) {
  int p1, p2, res;
  long int prod;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) {
    return 0;     /* TODO REG_NOT_EXIST */
  }

  prod = ((long) p1) * ((long) p2);
  if (prod > INT_MAX || prod < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  }

  res = stack_push(state, (int) prod);
  if (!res) {
    return 0;   /* TODO STACK_OVERFLOW */
  }

  return 1;
}

static int DIV(state_t *state, int params[]) {
  int p1, p2, res;
  int div;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) {
    return 0;     /* TODO REG_NOT_EXIST */
  }
  if (p2 == 0) {
    return 0;     /* TODO DIV_BY_ZERO */
  }

  div = p1 / p2;
  if (div > INT_MAX || div < INT_MIN) {
    return 0;       /* TODO OVERFLOW_ERROR */
  }

  res = stack_push(state, div);
  if (!res) {
    return 0;   /* TODO STACK_OVERFLOW */
  }

  return 1;
}

static int NOT_IMPL(state_t *state, int params[]) {
  return 0;       /* TODO NOT_IMPL or OP_CODE_NOT_VALID */
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
