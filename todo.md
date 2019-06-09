# TODO

## General
- Make more tests (.cvm)


## Idea
- Signal the ip value that generated the error (attention that ip may already point to the next instruction) (MAYBE MAINTAINING A COPY OF THE PREVIOUS/RUNNING IP) (each time i set a new ip, backup the old one)
- Interactive debugger (shows regs state, stack state)
- Throw warning if source code contains words not commented   <<<<<<<<<<<<<<
- Do some tests with incorrect code length
- Warning in case of unbalanced use of stack (probably not)
- Reorganize, rename, and comment .cvm test file
- array of valid ip position to signal if ip point to a non valid location
- maybe rewrite vm state without code array


## Questions
- How should we deal with syntax error
```
11
12s ; error (the 's' shouldn't be there)
11
```


## BUG


## Refactoring
- Comments / documentation
- Remove unneccessary includes
- Sort includes
- Maybe rename 'res' to 'error' or 'done'
- Maybe rename `code` into `source_code`
