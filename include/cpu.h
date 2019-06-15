/**
 * cpu.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef CPU_H
#define CPU_H


#include "vm-state.h"
#include "exception-manager.h"


/* define func_t type that represent a pointer to function that return an error_t and take 2 args (state, params) */
typedef error_t (*func_t)(state_t *state, int params[]);


error_t cpu_execute(state_t *state, int op_code, int params[]);


#endif
