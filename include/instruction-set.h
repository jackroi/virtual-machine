/**
 * instruction-set.h
 * Copyright © 2019 Giacomo Rosin | 875724 | P1G57
*/

#ifndef ISET_H
#define ISET_H

#define INSTRUCTIONS_NUMBER 34

int get_instruction_length(int op_code);
const char *get_instruction_name(int op_code);
const char *get_format(int op_code);


#endif
