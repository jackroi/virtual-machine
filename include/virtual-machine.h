/**
 * virtual-machine.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H


#define REGS_NUM 32
#include "exception-manager.h"

error_t vm_run(int command, const char *filename);


#endif
