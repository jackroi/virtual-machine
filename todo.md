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
- release memory at the end
- release memory on error (probably left to O.S.)
- implement INSTRUCTION_NOT_EXIST
- maybe refactor arrays length from int to size_t
- add ERROR in case of ip point to non valid location
- Should I do some kind of clean-up after last instruction (HALT) (reset regs, empty stack, ...)
- Check if `INT_MAX * INT_MAX` overflows `LONG_MAX`, if so i have to use another method to check `MUL` overflow (probably it works)
- Stack overflow/underflow exception
- Maybe doucument makefile better
- Remove bin folder and all the unnecessary .gitkeep
- Make more tests (.cvm)
- Rewrite stack without stack.c or implement get(i)
- Probably stack.c shold be removed, because i don't want SP duplication.


## Idea
- Encapsulate regs, stack, ip and sp into a module with some funcs to handle them.
The module could represent the vm status
- Maybe the vm should have a struct state that each
functions that manipulate the state carry it around
so, the number of parameter of the functions would be
be reduced, and avoid global variables
- Handle uppercase command line args
- Maybe create a file to store config (shared.c / shared.h ?) (for example instructions_array, ...)
- Create instruction-set or instructions to store shared variables
- Eventual flag to activate debug mode (DISPLAY shows the reg name, ...)
- get_format(op_code) -> return the format for printf of the instruction
- Signal the ip value that generated the error (attention that ip may already point to the next instruction)
- Print emojis and color terminal output
- Interactive debugger (shows regs state, stack state)


## Questions
- How should we deal with syntax error
```
11
12s ; error (the 's' shuoldn't be there)
11
```
- is JZ semantic revesed ?
- Need a better explanations
- Should PRINT_STACK thrown an error when SP < n ?


## BUG
- print_code does not print JMP, JZ, JPOS, JNEG correctly (due to the first argument not being a register but a literal) (probably fixable by implementing get_format(op_code), that returns the format of an instruction based on the op_code and probably a table of format...)
- rename stack_t type (if it's still used) for MacOS compatibility
- Stack size (16000 -> 16xyz)


## Refactoring
- Comments / documentation
- Remove unneccessary includes
- Sort includes
- Maybe rename 'res' to 'error' or 'done'
- Maybe rename `code` into `source_code`
