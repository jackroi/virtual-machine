; lines number
MOV R0 10        ; CHANGE HERE 10 -> 55
CALL foo
DISPLAY R30
MOV R0 100        ; CHANGE HERE 100 -> 5050
CALL foo
DISPLAY R30
MOV R0 1000        ; CHANGE HERE 1000 -> 5050
CALL foo
DISPLAY R30
HALT
; foo:
MOV R1 0        ; R1 : i = 0
MOV R20 1       ; R20: 1
MOV R30 0       ; R30: res = 0
; init_while:
SUB R0 R1       ; jump if i >= n
JNEG end
ADD R30 R1      ; res += i
POP R30
ADD R1 R20      ; i++
POP R1
JMP init_while
; end:
RET
