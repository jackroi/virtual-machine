/**
 * exceptio-manager.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

#define RETURN_IF_ERROR(expr, error) if (!expr) return error;

enum error {
  NO_ERROR = 0,
  MALLOC_ERROR = 1,
  CANNOT_OPEN_FILE = 2,
  INVALID_COMMAND = 3,
  ARGS_ERROR = 4,
  INVALID_CODE = 6,     /* TODO check if is covered by other errors */
  INVALID_INSTRUCTION = 7,
  INVALID_REG = 8,
  OVERFLOW_ERROR = 9,
  DIV_BY_ZERO = 10,
  STACK_OVERFLOW = 11,
  STACK_UNDEFLOW = 12,


  NOT_IMPLEMENTED = 100        /* TODO probably to remove */
};

typedef enum error error_t;


void log_error(error_t err_code);


#endif
