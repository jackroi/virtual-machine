# TODO

## General
- release memory at the end
- release memory on error (probably left to O.S.)
- add ERROR in case of ip point to non valid location (?)
- Should I do some kind of clean-up after last instruction (HALT) (reset regs, empty stack, ...)
- Make more tests (.cvm)
- More meaningful DISPLAY and PRINT_STACK outputs (maybe only in debug mode)


## Idea
- Encapsulate regs, stack, ip and sp into a module with some funcs to handle them.
The module could represent the vm status
- Maybe the vm should have a struct state that each
functions that manipulate the state carry it around
so, the number of parameter of the functions would be
be reduced, and avoid global variables
- Handle uppercase command line args (probably not needed)
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
- Should PRINT_STACK thrown an error when SP < n ? (probably not since it's used to debug )


## BUG
- Stack size (16000 -> 16xyz)
- Handle input of negative numbers


## Refactoring
- Comments / documentation
- Remove unneccessary includes
- Sort includes
- Maybe rename 'res' to 'error' or 'done'
- Maybe rename `code` into `source_code`
- `const` / `static` keyword where needed
- check if all header file use #ifdef
- maybe refactor arrays length from int to size_t
- Maybe doucument makefile better
