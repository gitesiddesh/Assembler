A  DS 4
L1 MOVER AREG, =’5’
ADD AREG, B
MOVEM AREG, A+2
D  EQU  A+1
L2  PRINT D
ORIGIN  L2+1
MOVER  CREG, C
ADD CREG, =’1’
MOVEM  CREG, A+3
LTORG
MOVER DREG, =’1’
ADD  DREG, C
MOVEM  DREG,   A
PRINT A+2
STOP
B  DS 1
C DS 1
END L1