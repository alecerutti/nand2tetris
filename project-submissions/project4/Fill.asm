@SCREEN
D=A
@index
M=D

(LOOP)
    @KBD
    D=M
    @COLOR_NEXT_PIXEL
    D;JGT
    @CLEAR_NEXT_PIXEL
    0;JMP

(COLOR_NEXT_PIXEL)
    @index
    D=M
    @KBD
    D=D-A
    @LOOP
    D;JEQ

    @index
    A=M
    M=-1

    @index
    M=M+1
    
    @LOOP
    0;JMP

(CLEAR_NEXT_PIXEL)
    @index
    D=M
    @SCREEN
    D=D-A
    @LOOP
    D;JLT

    @index
    A=M
    M=0

    @index
    M=M-1
    
    @LOOP
    0;JMP




