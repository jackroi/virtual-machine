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
- implement INSTRUCTION_NOT_EXIST


## Idea
- Encapsulate regs, stack, ip and sp into a module with some funcs to handle them.
The module could represent the vm status

- Maybe the vm should have a struct state that each
functions that manipulate the state carry it around
so, the number of parameter of the functions would be
be reduced, and avoid global variables


## Questions
- How should we deal with syntax error
```
11
12s ; error (the 's' shuoldn't be there)
11
```
