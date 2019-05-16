/**
 * stack.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Stack data structure
*/


#include "stack.h"

/**/
stack_t get_empty();

/**/
int is_empty(const stack_t *s);

/**/
int push(stack_t *s, int value);

/**/
int pop(stack_t *s, int *value);
