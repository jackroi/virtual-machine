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
  "invalid instruction pointer",
  "arithmetic overflow",
  "division by zero",
  "stack overflow",
  "stack underflow",

  "not implemented yet"     /* TODO check if it's still needed */
};

static const char *warning_messages[] = {
  "",
  "source code contains a value out of integer range",
};

/**/
void log_error(error_t err_code) {
  fprintf(stderr, "\033[1;31m");
  fprintf(stderr, "\n  ❌  ERROR [ %d ]:\t%s\n\n", err_code, error_messages[err_code]);
  fprintf(stderr, "\033[0m");
}

void log_warning(warning_t warn_code) {
  fprintf(stderr, "\033[01;33m");
  fprintf(stderr, "\n  ⚠️   WARNING [ %d ]:\t%s\n\n", warn_code, warning_messages[warn_code]);
  fprintf(stderr, "\033[0m");
}
