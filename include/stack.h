/**
 * stack.h
 * Copyright © 2019 Giacomo Rosin
*/

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 16000

struct stack {
  int data[STACK_SIZE];
  int sp;               /* ? where should i keep the stack pointer, here or on the struct ? */
};

typedef struct stack stack_t;   /* ? stack_t or *stack_t */


stack_t get_empty();
int is_empty(const stack_t *s);
int push(stack_t *s, int value);
int pop(stack_t *s, int *value);
int peek(const stack_t *s, int *value);


#endif
