/**
 * stack.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 16000      /* TODO shared */


int is_empty(const int *s);
int push(int *s, int value);
int pop(int *s, int *value);
int peek(const int *s, int n);


int stack_push(state_t *state, int value);
int stack_p(int *stack, int *sp, int value);


#endif
