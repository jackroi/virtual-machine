/**
 * cpu.h
 * Copyright © 2019 Giacomo Rosin
*/

#include "vm-state.h"

typedef int (*func_t)(state_t *state, int params[]);

enum op_code {
  HALT = 0,
  DISPLAY = 1,
  PRINT_STACK = 2,
  PUSH = 10,
  POP = 11,
  MOV = 12,
  CALL = 20,
  RET = 21,
  JMP = 22,
  JZ = 23,
  JPOS = 24,
  JNEG = 25,
  ADD = 30,
  SUB = 31,
  MUL = 32,
  DIV = 33
};


int cpu_execute(state_t *state, int op_code, int params[]);
