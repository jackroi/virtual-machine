; lines number
MOV R0 5
CALL foo
DISPLAY R30
HALT
; foo:
MOV R1 0
MOV R20 1
MOV R30 0
; init_while:
SUB R0 R1
JNEG end
ADD R30 R0
POP R30
ADD R1 R20
POP R1
JMP init_while
; end:
RET
