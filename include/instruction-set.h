/**
 * instruction-set.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef ISET_H
#define ISET_H

#define INSTRUCTION_NUMBER 34

int get_instrugtion_length(int op_code);
const char *get_instruction_name(int op_code);
const char *get_format(int op_code);


#endif