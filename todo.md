# TODO

## General
- const keyword where needed
- static keyword where needed
- error logger function
```c
void log_error(int err_code) {
  fprintf(stderr, "ERROR ...", err_code);   /* map err_code to a string */
}
```
- implement #ifdef in header file
- release memory on error (probably left to O.S.)


## Idea
- Encapsulate regs, stack, ip and sp into a module with some funcs to handle them.
The module could represent the vm status
