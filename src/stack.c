/**
 * stack.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Stack data structure
*/


#include "stack.h"

/**/
stack_t get_empty() {
  stack_t s;
  s.sp = 0;

  return s;
}

/**/
int is_empty(const stack_t *s) {
  return s->sp == 0;
}

/**/
int push(stack_t *s, int value) {
  if (s->sp < STACK_SIZE) {
    s->data[s->sp++] = value;
    return 1;
  } else {
    return 0;     /* ? maybe manage stack full from the caller */
  }
}

/**/
int pop(stack_t *s, int *value) {
  if (s->sp > 0) {
    *value = s->data[--(s->sp)];
    return 1;
  } else {
    return 0;     /* ? maybe manage stack full from the caller */
  }
}
