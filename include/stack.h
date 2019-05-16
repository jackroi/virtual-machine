/**
 * stack.h
 * Copyright © 2019 Giacomo Rosin
*/


struct stack {
  int data[16000];
  int sp;               /* ? where should i keep the stack pointer, here or on the struct ? */
};

typedef struct stack stack_t;   /* ? stack_t or *stack_t */


stack_t get_empty();
int is_empty(const stack_t *s);
int push(stack_t *s, int value);
int pop(stack_t *s, int *value);
