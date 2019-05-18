/**
 * parser.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef PARSER_H
#define PARSER_H


#include "exception-manager.h"

error_t parse_file(const char *filename, int **code, int *code_length);


#endif
