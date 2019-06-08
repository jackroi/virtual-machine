/**
 * parser.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef PARSER_H
#define PARSER_H

#include <stddef.h>
#include "exception-manager.h"

error_t parse_file(const char *filename, int **code, size_t *code_length);


#endif
