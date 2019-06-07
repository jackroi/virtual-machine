/**
 * exception-manager.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Logging functions
*/

#include <stdio.h>
#include "exception-manager.h"


static const char *error_messages[] = {
  "",
  "malloc failed",
  "cannot open file",
  "invalid command",
  "expected 2 arguments",
  "invalid machine code",
  "invalid instruction found",
  "invalid register number",
  "arithmetic overflow",
  "division by zero",
  "stack overflow",
  "stack underflow",

  "not implemented yet"
};


/**/
void log_error(error_t err_code) {
  fprintf(stderr, "ERROR [ %d ]:\t%s\n", err_code, error_messages[err_code]);
}
