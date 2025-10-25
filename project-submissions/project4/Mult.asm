@R2
M=0


@R0
D=M
@END
D;JEQ


@1
D=D-A
@R0_ONE
D;JEQ


@R1
D=M // D=R1

@END
D;JEQ


@1
D=D-A
@R1_ONE
D;JEQ

@R0
D=M
@addend
M=D 

@R1
D=M
@iterations
M=D

(LOOP)
    @R2
    D=M
    @addend
    D=D+M
    @R2
    M=D
    
    @iterations
    D=M
    D=D-1
    M=D
    @LOOP
    D;JGT
    @END
    0;JMP

(R0_ONE)
    @R1
    D=M
    @R2
    M=D
    @END
    0;JMP

(R1_ONE)
    @R0
    D=M
    @R2
    M=D
    @END
    0;JMP

(END)