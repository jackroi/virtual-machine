# TODO

## General
- (x) release memory at the end
- (x) release memory on error (probably left to O.S.)
- (x) add ERROR in case of ip point to non valid location (?)
- Make more tests (.cvm)
- (x) Generate warning if an argument is out of integer range
- IP and SP -> unsigned int (maybe)


## Idea
- (x) Encapsulate regs, stack, ip and sp into a module with some funcs to handle them. The module could represent the vm status
- (x) Maybe the vm should have a struct state that each
functions that manipulate the state carry it around
so, the number of parameter of the functions would be
be reduced, and avoid global variables
- (x) Create instruction-set or instructions to store shared variables
- Eventual flag to activate debug mode (DISPLAY shows the reg name, ...) (maybe but in another way)
- (x) get_format(op_code) -> return the format for printf of the instruction
- Signal the ip value that generated the error (attention that ip may already point to the next instruction) (MAYBE MAINTAINING A COPY OF THE PREVIOUS/RUNNING IP) (each time i set a new ip, backup the old one)
- (x) Print emojis and color terminal output
- Interactive debugger (shows regs state, stack state)
- Throw warning if source code contains words not commented   <<<<<<<
- Do some tests with incorrect code length
- Warning in case of unbalanced use of stack (probably not)
- Reorganize, rename, and comment .cvm test file


## Questions
- How should we deal with syntax error
```
11
12s ; error (the 's' shouldn't be there)
11
```


## BUG
- (x) Stack size (16000 -> 16xyz)
- (x) Handle input of negative numbers
- Warning / (ERROR) when source code length field is bigger than the actual length    <<<<<<
- Warning if HALT is missing (and avoid heap buffer overflow in vm main loop)


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
- Give the right type to variables (ip -> unsigned int)
