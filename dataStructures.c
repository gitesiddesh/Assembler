typedef struct errors{

	int lineNo;
	char data[80];
	struct errors *next;
}Error;

Error *errorHead = NULL;

char *Mnemonic[11]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};

char *Register[4]={"AREG","BREG","CREG","DREG"};

char *Condition[6]={"LT","LE","EQ","GT","GE","ANY"};

char *Declarative[2]={"DS","DC"};

char *AssemblyDir[5]={"START","END","ORIGIN","LTORG","EQU"};
