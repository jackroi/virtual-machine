/**
 * cpu.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Where the instructions are implemented
*/

#include "cpu.h"
#include "vm-state.h"
#include "exception-manager.h"
#include <stdio.h>
#include <limits.h>

/*static int HALT()*/

/* TODO what should each func return ? */

static error_t DISPLAY(state_t *state, int params[]) {
  int value, res;

  res = get_register(state, params[0], &value);
  if (!res) return INVALID_REG;

  printf("REG [%2d]:\t%d\n", params[0], value);      /* TODO print more util message ? */
  return NO_ERROR;
}

/* print from sp - 1 to sp - n inclued */
static error_t PRINT_STACK(state_t *state, int params[]) {
  int to_peek, value, i;

  printf("\n");

  i = 0;
  to_peek = params[0];
  while (i < to_peek && stack_peek(state, i, &value)) {
    printf("STACK [%3d]:\t %d\n", i, value);
    i++;
  }

  printf("\n");

  return NO_ERROR;
}


static error_t PUSH(state_t *state, int params[]) {
  int value, res;
  res = get_register(state, params[0], &value);
  if (!res) return INVALID_REG;

  res = stack_push(state, value);
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;
}


static error_t POP(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) return STACK_UNDERFLOW;

  res = set_register(state, params[0], value);
  if (!res) return INVALID_REG;

  return NO_ERROR;
}


static error_t MOV(state_t *state, int params[]) {
  int res;

  res = set_register(state, params[0], params[1]);
  if (!res) return INVALID_REG;

  return NO_ERROR;
}


static error_t CALL(state_t *state, int params[]) {
  int res;

  res = stack_push(state, get_ip(state));
  if (!res) return STACK_OVERFLOW;

  res = set_ip(state, params[0]);
  if (!res) return INVALID_IP;

  return NO_ERROR;
}


static error_t RET(state_t *state, __attribute__((unused)) int params[]) {    /* ! params not used */
  int value, res;

  res = stack_pop(state, &value);
  if (!res) return STACK_UNDERFLOW;

  res = set_ip(state, value);
  if (!res) return INVALID_IP;

  return NO_ERROR;
}


static error_t JMP(state_t *state, int params[]) {
  int res;

  res = set_ip(state, params[0]);
  if (!res) return INVALID_IP;

  return NO_ERROR;
}


static error_t JZ(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) return STACK_UNDERFLOW;

  if (value == 0) {
    res = set_ip(state, params[0]);
    if (!res) return INVALID_IP;
  }

  return NO_ERROR;
}


static error_t JPOS(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) return STACK_UNDERFLOW;

  if (value > 0) {
    res = set_ip(state, params[0]);
    if (!res) return INVALID_IP;
  }

  return NO_ERROR;
}


static error_t JNEG(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);
  if (!res) return STACK_UNDERFLOW;

  if (value < 0) {
    res = set_ip(state, params[0]);
    if (!res) return INVALID_IP;
  }

  return NO_ERROR;
}


static error_t ADD(state_t *state, int params[]) {
  int p1, p2, res;
  long int sum;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) return INVALID_REG;

  sum = ((long) p1) + ((long) p2);
  if (sum > INT_MAX || sum < INT_MIN) {   /* ? inline ? */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) sum);
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;
}


static error_t SUB(state_t *state, int params[]) {
  int p1, p2, res;
  long int diff;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) return INVALID_REG;

  diff = ((long) p1) - ((long) p2);
  if (diff > INT_MAX || diff < INT_MIN) {   /* ? inline ? */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) diff);
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;
}


static error_t MUL(state_t *state, int params[]) {
  int p1, p2, res;
  long int prod;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) return INVALID_REG;

  prod = ((long) p1) * ((long) p2);
  if (prod > INT_MAX || prod < INT_MIN) {
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) prod);
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;
}


static error_t DIV(state_t *state, int params[]) {
  int p1, p2, res;
  long int div;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);
  if (!res) return INVALID_REG;
  if (p2 == 0) return DIV_BY_ZERO;

  div = ((long) p1) / ((long) p2);
  if (div > INT_MAX || div < INT_MIN) {
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, div);
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;
}


static error_t NOT_IMPL(__attribute__((unused)) state_t *state, __attribute__((unused)) int params[]) {       /* ! params not used */
  return INVALID_INSTRUCTION;       /* TODO NOT_IMPL or OP_CODE_NOT_VALID */
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
error_t cpu_execute(state_t *state, int op_code, int params[]) {
  if (op_code > 33 || op_code < 0) {        /* TODO define */
    return INVALID_INSTRUCTION;
  } else {
    return instr_func[op_code](state, params);
  }
}
