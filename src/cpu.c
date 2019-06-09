/**
 * cpu.c
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
 *
 * Where the machine instructions are implemented.
*/

#include <stdio.h>
#include <limits.h>
#include "cpu.h"
#include "vm-state.h"
#include "instruction-set.h"
#include "exception-manager.h"


static error_t HALT(__attribute__((unused)) state_t *state, __attribute__((unused)) int params[]);
static error_t DISPLAY(state_t *state, int params[]);
static error_t PRINT_STACK(state_t *state, int params[]);
static error_t PUSH(state_t *state, int params[]);
static error_t POP(state_t *state, int params[]);
static error_t MOV(state_t *state, int params[]);
static error_t CALL(state_t *state, int params[]);
static error_t RET(state_t *state, __attribute__((unused)) int params[]);
static error_t JMP(state_t *state, int params[]);
static error_t JZ(state_t *state, int params[]);
static error_t JPOS(state_t *state, int params[]);
static error_t JNEG(state_t *state, int params[]);
static error_t ADD(state_t *state, int params[]);
static error_t SUB(state_t *state, int params[]);
static error_t MUL(state_t *state, int params[]);
static error_t DIV(state_t *state, int params[]);
static error_t NOT_IMPL(__attribute__((unused)) state_t *state, __attribute__((unused)) int params[]);

/* array of pointer to functions that maps instruction code with the function that implement that precise instruction */
static const func_t instr_func[INSTRUCTIONS_NUMBER] = {
  HALT,
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


/**
 * cpu_execute: execute the instruction and update the vm state accordingly
 * - state: pointer to the state of the vm (contains ip, sp, stack, regs, ...)
 * return an exit status to signal eventual errors
 */
error_t cpu_execute(state_t *state, int op_code, int params[]) {
  if (op_code >= INSTRUCTIONS_NUMBER || op_code < 0) {      /* check if op_code is inside of the instruction number range */
    return INVALID_INSTRUCTION;                             /* return error code */
  } else {
    return instr_func[op_code](state, params);              /* call the function pointed by the op_code cell of the instr_func array (array of function pointers) */
  }
}


/**
 * HALT: marks the end of a program (parameters not used)
 */
static error_t HALT(__attribute__((unused)) state_t *state, __attribute__((unused)) int params[]) {
  return NO_ERROR;
}

/**
 * DISPLAY: print in the stdout the value of a register
 * - state: pointer to vm state
 * - params[0]: register code
 * return an exit status to signal eventual errors
 */
static error_t DISPLAY(state_t *state, int params[]) {
  int value, res;

  res = get_register(state, params[0], &value);           /* get the value contained in the given register */
  if (!res) return INVALID_REG;                           /* catch error */

  printf("REG [%2d]:\t%d\n", params[0], value);

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * PRINT_STACK: print in the stdout the top n elements of a stack
 * - state: pointer to vm state
 * - params[0]: number of elements to print
 * return an exit status to signal eventual errors
 */
static error_t PRINT_STACK(state_t *state, int params[]) {
  int to_peek, value, i;

  printf("\n");

  /* print the top n value of the stack */
  i = 0;
  to_peek = params[0];
  while (i < to_peek && stack_peek(state, i, &value)) {   /* stop when printed enough elements or when printed all the elements */
    printf("STACK [%2d]:\t %d\n", i, value);              /* peek and print element [sp - i - 1] from the stack */
    i++;
  }

  printf("\n");

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * PUSH: push a register into the stack
 * - state: pointer to vm state
 * - params[0]: register code
 * return an exit status to signal eventual errors
 */
static error_t PUSH(state_t *state, int params[]) {
  int value, res;
  res = get_register(state, params[0], &value);           /* get the value contained in the given register */
  if (!res) return INVALID_REG;                           /* catch error */

  res = stack_push(state, value);                         /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;                        /* catch error */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * POP: pop an item from the stack and save it into a register
 * - state: pointer to vm state
 * - params[0]: register code
 * return an exit status to signal eventual errors
 */
static error_t POP(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);                         /* pop element from the stack */
  if (!res) return STACK_UNDERFLOW;                       /* catch error */

  res = set_register(state, params[0], value);            /* set the given register equal to value */
  if (!res) return INVALID_REG;                           /* catch error */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * MOV: copy a value into a register
 * - state: pointer to vm state
 * - params[0]: register code
 * - params[1]: value to copy
 * return an exit status to signal eventual errors
 */
static error_t MOV(state_t *state, int params[]) {
  int res;

  res = set_register(state, params[0], params[1]);        /* set the given register equal to the given value */
  if (!res) return INVALID_REG;                           /* catch error */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * CALL: call a subrutine, push ip and jump to the given position
 * - state: pointer to vm state
 * - params[0]: position to jump to
 * return an exit status to signal eventual errors
 */
static error_t CALL(state_t *state, int params[]) {
  int res;

  res = stack_push(state, get_ip(state));                 /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;                        /* catch error */

  set_ip(state, params[0]);                               /* set instruction pointer equal to the given value */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * RET: return from subrutine call, pop to ip
 * - state: pointer to vm state
 * return an exit status to signal eventual errors
 */
static error_t RET(state_t *state, __attribute__((unused)) int params[]) {
  int value, res;

  res = stack_pop(state, &value);                         /* pop element from the stack */
  if (!res) return STACK_UNDERFLOW;                       /* catch error */

  set_ip(state, value);                                   /* set instruction pointer equal to the given value */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * JMP: jump to the given position by replacing ip with the given value
 * - state: pointer to vm state
 * - params[0]: position to jump to
 * return an exit status to signal eventual errors
 */
static error_t JMP(state_t *state, int params[]) {
  set_ip(state, params[0]);                               /* set instruction pointer equal to the given value */

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * JZ: pop a value from the stack and jump to the given position if the value is equal to 0
 * - state: pointer to vm state
 * - params[0]: position to jump to
 * return an exit status to signal eventual errors
 */
static error_t JZ(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);                         /* pop element from the stack */
  if (!res) return STACK_UNDERFLOW;                       /* catch error */

  if (value == 0) {
    set_ip(state, params[0]);                             /* if popped value is equal to 0 then jump */
  }

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * JPOS: pop a value from the stack and jump to the given position if the value is greater than 0
 * - state: pointer to vm state
 * - params[0]: position to jump to
 * return an exit status to signal eventual errors
 */
static error_t JPOS(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);                         /* pop element from the stack */
  if (!res) return STACK_UNDERFLOW;                       /* catch error */

  if (value > 0) {
    set_ip(state, params[0]);                             /* if popped value is greater than 0 then jump */
  }

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * JNEG: pop a value from the stack and jump to the given position if the value is less than 0
 * - state: pointer to vm state
 * - params[0]: position to jump to
 * return an exit status to signal eventual errors
 */
static error_t JNEG(state_t *state, int params[]) {
  int value, res;

  res = stack_pop(state, &value);                         /* pop element from the stack */
  if (!res) return STACK_UNDERFLOW;                       /* catch error */

  if (value < 0) {
    set_ip(state, params[0]);                             /* if popped value is less than 0 then jump */
  }

  return NO_ERROR;                                        /* no error, everything went fine */
}

/**
 * ADD: push into the stack the sum of the two given registers
 * - state: pointer to vm state
 * - params[0]: first register code
 * - params[1]: second register code
 * return an exit status to signal eventual errors
 */
static error_t ADD(state_t *state, int params[]) {
  int p1, p2, res;
  long int sum;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);   /* get the values from the 2 regs */
  if (!res) return INVALID_REG;                   /* catch error */

  sum = ((long) p1) + ((long) p2);                /* take advantage of long int type to simplify overflow detection */
  if (sum > INT_MAX || sum < INT_MIN) {           /* catch error */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) sum);             /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;                                /* no error, everything went fine */
}

/**
 * SUB: push into the stack the difference of the two given registers
 * - state: pointer to vm state
 * - params[0]: first register code
 * - params[1]: second register code
 * return an exit status to signal eventual errors
 */
static error_t SUB(state_t *state, int params[]) {
  int p1, p2, res;
  long int diff;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);   /* get the values from the 2 regs */
  if (!res) return INVALID_REG;                    /* catch error */

  diff = ((long) p1) - ((long) p2);                /* take advantage of long int type to simplify overflow detection */
  if (diff > INT_MAX || diff < INT_MIN) {          /* catch error */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) diff);             /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;

  return NO_ERROR;                                 /* no error, everything went fine */
}

/**
 * MUL: push into the stack the product of the two given registers
 * - state: pointer to vm state
 * - params[0]: first register code
 * - params[1]: second register code
 * return an exit status to signal eventual errors
 */
static error_t MUL(state_t *state, int params[]) {
  int p1, p2, res;
  long int prod;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);   /* get the values from the 2 regs */
  if (!res) return INVALID_REG;                    /* catch error */

  prod = ((long) p1) * ((long) p2);                /* take advantage of long int type to simplify overflow detection */
  if (prod > INT_MAX || prod < INT_MIN) {          /* catch error */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, (int) prod);             /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;                 /* catch error */

  return NO_ERROR;                                 /* no error, everything went fine */
}

/**
 * DIV: push into the stack the quootient of the two given registers
 * - state: pointer to vm state
 * - params[0]: first register code
 * - params[1]: second register code
 * return an exit status to signal eventual errors
 */
static error_t DIV(state_t *state, int params[]) {
  int p1, p2, res;
  long int div;

  res = get_register(state, params[0], &p1) && get_register(state, params[1], &p2);   /* get the values from the 2 regs */
  if (!res) return INVALID_REG;                   /* catch error */
  if (p2 == 0) return DIV_BY_ZERO;                /* catch error */

  div = ((long) p1) / ((long) p2);                /* take advantage of long int type to simplify overflow detection */
  if (div > INT_MAX || div < INT_MIN) {           /* catch error */
    return OVERFLOW_ERROR;
  }

  res = stack_push(state, div);                   /* push register value into the stack */
  if (!res) return STACK_OVERFLOW;                /* catch error */

  return NO_ERROR;                                /* no error, everything went fine */
}

/**
 * NOT_IMPL: instruction not provided by this instruction set
 * return INVALID_INSTRUCTION error
 */
static error_t NOT_IMPL(__attribute__((unused)) state_t *state, __attribute__((unused)) int params[]) {
  return INVALID_INSTRUCTION;                     /* return always an error */
}
