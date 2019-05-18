/**
 * exceptio-manager.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef EXCEPTION_MANAGER_H
#define EXCEPTION_MANAGER_H

enum error {
  NO_ERROR = 0,
  MALLOC_ERROR = 1,
  CANNOT_OPEN_FILE = 2,
  INVALID_COMMAND = 3,
  ARGS_ERROR = 4,
  INVALID_CODE = 6,
  NOT_IMPLEMENTED = 10        /* TODO probably to remove */
};

typedef enum error error_t;


void log_error(error_t err_code);


#endif
