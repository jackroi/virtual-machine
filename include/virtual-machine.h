/**
 * virtual-machine.h
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
*/

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#include "exception-manager.h"


/* define type command_t that represents the possible shell arguments */
enum command {
  NO_COMMAND = 0,
  PRINT = 1,
  RUN = 2
};

typedef enum command command_t;


error_t vm_run(command_t command, const char *filename);


#endif
