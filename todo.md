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
- maybe refactor arrays length from int to size_t
- add ERROR in case of ip point to non valid location
- Should I do some kind of clean-up after last instruction (HALT)
- Comments / documentation


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
- is JZ semantic revesed ?
- Need a better explanations

## BUG
- print_code does not print JMP, JZ, JPOS, JNEG correctly (due to the first argument not being a register but a literal)
