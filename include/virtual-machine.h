/**
 * virtual-machine.h
 * Copyright © 2019 Giacomo Rosin
*/

#define REGS_NUM 32

error_t vm_run(int command, const char *filename);
