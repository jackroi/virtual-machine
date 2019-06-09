/**
 * exception-manager.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H


#define MAX_INSTR_LENGTH 3


/* define error_t type that represent the possible errors */
enum error {
  NO_ERROR = 0,
  MALLOC_ERROR = 1,
  CANNOT_OPEN_FILE = 2,
  INVALID_COMMAND = 3,
  ARGS_ERROR = 4,
  INVALID_CODE = 5,     /* TODO check if is covered by other errors */  /* raised with a static check */
  INVALID_INSTRUCTION = 6,
  INVALID_REG = 7,
  INVALID_IP = 8,
  OVERFLOW_ERROR = 9,
  DIV_BY_ZERO = 10,
  STACK_OVERFLOW = 11,
  STACK_UNDERFLOW = 12,

  NOT_IMPLEMENTED = 13        /* TODO probably to remove */
};

typedef enum error error_t;


/* define warning_t type that represent the possible warnings */
enum warning {
  INSTRUCTION_OVERFLOW = 1,
  MISSING_HALT = 2,
  DECLARED_LENGTH_DIFFER_FROM_ACTUAL = 3
};

typedef enum warning warning_t;


void log_error(error_t err_code);
void log_warning(warning_t warn_code);


#endif
