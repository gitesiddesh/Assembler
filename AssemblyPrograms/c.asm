START 500 
A DS 1  
B DS 1 
C DC ‘0’ 
READ A  
READ B 
MOVER   AREG, A  
MULT   AREG, B 
MOVEM   AREG, C 
PRINT C
STOP
END

 