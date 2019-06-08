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

  "not implemented yet"     /* TODO check if it's still needed */
};


/**/
void log_error(error_t err_code) {
  fprintf(stderr, "\033[1;31m");
  fprintf(stderr, "\n  ❌  ERROR [ %d ]:\t%s\n\n", err_code, error_messages[err_code]);
  fprintf(stderr, "\033[0m");
}
