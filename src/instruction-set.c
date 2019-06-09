/**
 * instruction-set.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Instruction set
*/

#include "instruction-set.h"


static const char *instructions_name[INSTRUCTION_NUMBER] = {
  "HALT",
  "DISPLAY",
  "PRINT_STACK",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "PUSH",
  "POP",
  "MOV",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "CALL",
  "RET",
  "JMP",
  "JZ",
  "JPOS",
  "JNEG",
  "",
  "",
  "",
  "",
  "ADD",
  "SUB",
  "MUL",
  "DIV"
};

static const int instructions_length[INSTRUCTION_NUMBER] = {

  1,
  2,
  2,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  2,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  2,
  1,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3
};

static const char *instructions_format[INSTRUCTION_NUMBER] = {
  "[%3d]\tHALT\n",
  "[%3d]\tDISPLAY R%d\n",
  "[%3d]\tPRINT_STACK %d\n",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "[%3d]\tPUSH R%d\n",
  "[%3d]\tPOP R%d\n",
  "[%3d]\tMOV R%d %d\n",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "[%3d]\tCALL %d\n",
  "[%3d]\tRET\n",
  "[%3d]\tJMP %d\n",
  "[%3d]\tJZ %d\n",
  "[%3d]\tJPOS %d\n",
  "[%3d]\tJNEG %d\n",
  "",
  "",
  "",
  "",
  "[%3d]\tADD R%d R%d\n",
  "[%3d]\tSUB R%d R%d\n",
  "[%3d]\tMUL R%d R%d\n",
  "[%3d]\tDIV R%d R%d\n"
};


int get_instruction_length(int op_code) {
  return instructions_length[op_code];
}

const char *get_instruction_name(int op_code) {
  return instructions_name[op_code];
}

const char *get_format(int op_code) {
  return instructions_format[op_code];
}
