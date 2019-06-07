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
  INVALID_CODE = 5,     /* TODO check if is covered by other errors */
  INVALID_INSTRUCTION = 6,
  INVALID_REG = 7,
  OVERFLOW_ERROR = 8,
  DIV_BY_ZERO = 9,
  STACK_OVERFLOW = 10,
  STACK_UNDERFLOW = 11,

  NOT_IMPLEMENTED = 12        /* TODO probably to remove */
};

typedef enum error error_t;


void log_error(error_t err_code);


#endif
