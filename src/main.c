/**
 * main.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Entry point
*/


#include <string.h>
#include <ctype.h>
#include "virtual-machine.h"


static parse_command(const char *cmd);


int main(int argc, char const *argv[]) {
  int error, command;

  if (argc == 3) {
    command = parse_command(argv[1]);

    if (!command) {
      error = INVALID_COMMAND;
    } else {
      vm_run(command, argv[2]);         /* start the virtual machine */
    }
  } else {
    error = ARGS_ERROR;
  }


  if (error) {
    log_error(error);
  }

  return error;
}


static parse_command(const char *cmd) {
  int c;
  if (!strcmp(cmd, "print") || !strcmp(cmd, "stampa")) {
    c = 1;
  } else if (!strcmp(cmd, "print") || !strcmp(cmd, "stampa")) {
    c = 2;
  } else {
    c = 0;
  }

  return c;
}
