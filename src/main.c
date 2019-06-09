/**
 * main.c
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
 *
 * Entry point: takes the arguments from command line,
 * parses them and starts the virtual machine.
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "virtual-machine.h"


static command_t parse_command(const char *cmd);

/**
 * main: take the argument from command line,
 * parse them and start the virtual machine
 * - argv[1]: virtual machine command (stampa / esegui) (print / run)
 * - argv[2]: source code path (file .cvm)
 * return the exit status
 */
int main(int argc, char const *argv[]) {
  int error;
  command_t command;

  setbuf(stdout, NULL);                         /* always flush stdout buffer */
  setbuf(stderr, NULL);                         /* always flush stderr buffer */

  if (argc == 3) {                              /* right number of args */
    command = parse_command(argv[1]);           /* try to parse the command */

    if (!command) {                             /* if no command is found */
      error = INVALID_COMMAND;                  /* set error flag */
    } else {                                    /* else if a valid command is found */
      error = vm_run(command, argv[2]);         /* start the virtual machine and execute the command*/
    }
  } else {                                      /* incorrect number of args */
    error = ARGS_ERROR;                         /* set error flag */
  }


  if (error) {                                  /* if any error has occurred */
    log_error(error);                           /* log the corresponding message on the console */
  }

  return error;                                 /* return the exit status to the shell */
}

/**
 * parse_command: parse the input string
 * return the code of the command or 0 if no valid command is found
 */
static command_t parse_command(const char *cmd) {
  command_t c;

  /* match the command with its own code */
  if (!strcmp(cmd, "print") || !strcmp(cmd, "stampa")) {        /* cmd is 'print' or 'stampa' */
    c = PRINT;
  } else if (!strcmp(cmd, "run") || !strcmp(cmd, "esegui")) {   /* cmd is 'run' or 'esegui'  */
    c = RUN;
  } else {                                                      /* no command found */
    c = NO_COMMAND;
  }

  return c;                                                     /* return the code */
}
