START 200 
READ A 
MOVER      AREG, A 
BACK PRINT A 
ADD AREG, ONE 
MOVEM   AREG,  A 
COMP AREG, TEN 
BC LT BACK 
STOP 
A DC ‘1’ 
ONE DC ‘1’ 
TEN DC ‘10’ 
END 