/**
 * stack.c
 * Copyright © 2019 Giacomo Rosin
 *
 * Stack data structure
*/


#include "stack.h"


/**/
int is_empty(const int *s) {
  return s->sp == 0;
}

/**/
int push(int *s, int value) {
  if (s->sp < STACK_SIZE) {
    s->data[s->sp++] = value;
    return 1;
  } else {
    return 0;     /* ? maybe manage stack full from the caller */
  }
}

/**/
int pop(int *s, int *value) {
  if (s->sp > 0) {
    *value = s->data[--(s->sp)];
    return 1;
  } else {
    return 0;     /* ? maybe manage stack full from the caller */
  }
}
