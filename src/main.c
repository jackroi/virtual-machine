/**
 * main.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Entry point
*/


#include <stdio.h>
#include "virtual-machine.h"


int main(int argc, char const *argv[]) {
  int error;

  /* // ? maybe reorder this if statement */
  if (argc == 1) {
    printf("ERROR #%d:\tnot implemented yet", 10);     /* TODO log error func */
    error = 10;
  } else if (argc == 3) {
    /* TODO manage args transform argv[1] int an the code of the command */
    int command = 1; // ! temp placeholder (? vm_parse_cmd() ?)
    error = vm_run(command, argv[2]);
  } else {
    printf("ERROR #%d:\tnumnber of arguments not correct (need 2 args)", 1);         /* TODO log error func */
    error = 1;
  }

  return error;
}
