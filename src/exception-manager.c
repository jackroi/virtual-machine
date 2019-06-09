/**
 * exception-manager.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Exception manager: provides error and warning codes definitions and logging functions
*/

#include <stdio.h>
#include "exception-manager.h"

/* array that maps error codes with the corresponding error messages */
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

  "not implemented yet"
};

/* array that maps warning codes with the corresponding warning messages */
static const char *warning_messages[] = {
  "",
  "source code contains a value out of integer range",
  "source code doesn't contain HALT instructions, the program may have unwanted behaviour",
  "declared source code length is greater than the actual number of instructions"
};

/**
 * log_error: log in the stderr the message corresponding to the error code
 * - err_code: error code
 */
void log_error(error_t err_code) {
  fprintf(stderr, "\033[1;31m");
  fprintf(stderr, "\n  ❌  ERROR [ %d ]:\t%s\n\n", err_code, error_messages[err_code]);
  fprintf(stderr, "\033[0m");
}

/**
 * log_error: log in the stderr the message corresponding to the warning code
 * - err_code: error code
 */
void log_warning(warning_t warn_code) {
  fprintf(stderr, "\033[01;33m");
  fprintf(stderr, "\n  ⚠️   WARNING [ %d ]:\t%s\n\n", warn_code, warning_messages[warn_code]);
  fprintf(stderr, "\033[0m");
}
