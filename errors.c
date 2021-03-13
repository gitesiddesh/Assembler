
void findError(int C){

	FILE *ptr=fopen(fileName,"r");
	char line[80];
	int lineCount=1; // temp local variable


	while(!feof(ptr)){
		fgets(line,80,ptr);
		noOftokens=sscanf(line,"%s %s %s %s",op1,op2,op3,op4);

		switch(noOftokens)
		{
			case 1: 
			{
				if(strcasecmp("END",op1)==0 || strcasecmp("STOP",op1)==0 || strcasecmp("LTORG",op1)==0)
					;
				else
					addError(lineCount,"Invalid Mnemonic Instruction");
			}
			break;

			case 2:
			{
				if(!check("All",op1)){

					if(strcasecmp("STOP",op2)!=0)
						addError(lineCount,"Invalid Mnemonic Instruction");
				}
				else if(check("All",op1)){
					if(strcasecmp("STOP",op2)==0)
							addError(lineCount,"Invalid Symbolic Name");
					else if(strcasecmp("READ",op1)==0 || strcasecmp("PRINT",op1)==0 || strcasecmp("END",op1)==0)
						if(check("All",op2))
							addError(lineCount,"Invalid Symbolic Name");
					else if(strcasecmp("START",op1)==0)
						if(isdigit(op2[0])==0)
							addError(lineCount,"Invalid Constant");
					else if(strcasecmp("ORIGIN",op1)==0)
						if(check("All",op2))
							addError(lineCount,"Invalid Address Specifier");
				}
			}
			break;

			case 3: 
			{	// if first operand is Mnemonic 
				if(check("Mnemonic",op1) && strcasecmp("STOP",op1)!=0 && strcasecmp("READ",op1)!=0 && strcasecmp("PRINT",op1)!=0){
					
					if(strcmp(op1,"BC")==0)
					{
						if(!check("Condition",op2))
							addError(lineCount,"Invalid Symbolic Name1");
						if(check("All",op3))
							addError(lineCount,"Invalid Symbolic Name2");
					}
					else{                       // condition for ADD, SUB, MUL, DIV, COMP, MOVEM, MOVER
						char tmp[20];
						int k=strlen(op2)-1,i;
						if(op2[k]!=',')
							addError(lineCount,"Invalid Register Operand3");
						else
						{
							for(i=0;i<k;i++)
								tmp[i]=op2[i];
							tmp[i]='\0';
						if(check("Register",op2))
							addError(lineCount,"Invalid Register Operand4");
						}
						if(check("All",op3))
							addError(lineCount,"Invalid Symbolic Name5");
					}
				}
				else{   // if first operand is not Mnemonic

					if(!check("All",op1)){

						if(strcasecmp("READ",op2)==0 || strcasecmp("PRINT",op2)==0)
							if(check("All",op3))
								addError(lineCount,"Invalid Symbolic Name6");

						if(check("Declarative",op2))
							if(check("All",op3)) 
								addError(lineCount,"Invalid Constant7");

						if(strcasecmp("EQU",op2)==0)
							if(check("All",op3))
								addError(lineCount,"Invalid Address Specifiers8");
							}
					}

					if(strcasecmp("READ",op2)==0 || strcasecmp("PRINT",op2)==0 || strcasecmp("EQU",op2)==0)
						if(!check("All",op3))
							if(check("All",op1))
								addError(lineCount,"Invalid Symbolic Name");
					

					if(check("Declarative",op2))
						if(check("All",op1))
							addError(lineCount,"Invalid Symbolic Name");

					/*if(isdigit(op3[0])!=0 || isdigit(op3[1])!=0)
						if(!check("All",op1))
							if(!check("Declarative",op2))
								addError(lineCount,"Invalid Mnemonic Instruction10");*/

					if(strcasecmp("AREG,",op2)==0 || strcasecmp("BREG,",op2)==0 || strcasecmp("CREG,",op2)==0 || strcasecmp("DREG,",op2)==0)
						if(!check("All",op3))
							if(!check("Mnemonic",op1))
								addError(lineCount,"Invalid Mnemonic Instruction11");
				}				
			break;

			case 4:
			{
				if(check("Mnemonic",op1) || check("Mnemonic",op4)){
					addError(lineCount,"Invalid Symbolic Name");
				}
				if(check("Register",op1) || check("Register",op4)){
					addError(lineCount,"Invalid Symbolic Name");
				}
				if(check("Condition",op1) || check("Condition",op4)){
					addError(lineCount,"Invalid Symbolic Name");
				}
				if(check("Declarative",op1) || check("Declarative",op4)){
					addError(lineCount,"Invalid Symbolic Name");
				}
				if(check("AssemblyDir",op1) || check("AssemblyDir",op4)){
					addError(lineCount,"Invalid Symbolic Name");
				}

				if(!check("Mnemonic",op2)){
					addError(lineCount,"Invalid Mnemonic Instruction");
				}

				//for operand 3...register operand
				char tmp[20];
				int k=strlen(op3)-1,i;
				if(op3[k]!=',')
					addError(lineCount,"Invalid Register Operand3");
				else
				{
					for(i=0;i<k;i++)
						tmp[i]=op3[i];
					tmp[i]='\0';
				if(check("Register",op3))
					addError(lineCount,"Invalid Register Operand4");
				}
			}
			break;
		}
		//printf("\n%d\t%s",lineCount,line);
		lineCount++;
		LC++;
	}

}

void addError(int lineNo,char error[]){   // adding errors to linked-list
	Error *new=newError;
	new->lineNo=lineNo;
	strcpy(new->data,error);

	if(errorHead==NULL){
		errorHead=new;
		errorHead->next=NULL;
		return;
	}

	Error *temp=errorHead;

	while(temp->next!=NULL){
		if(temp->lineNo==new->lineNo && strcasecmp(temp->data,new->data)){  //check if any error is getting repeated
			free(new);      // free memory allocated 
			return;			
		}
		temp=temp->next;
	}

	temp->next=new;
	new->next=NULL;
}

void printErrors(){
	if(errorHead==NULL)
		printf("\nNo errors.");
	else{

		Error *temp=errorHead;
		while(temp!=NULL){
			printf("\nError on line %d.....{%s}",temp->lineNo,temp->data);
			temp=temp->next;
		}
	}
}

bool check(char chkInto[],char chk[]){      // check if, token exist in any of pre-defined tables i.e Mnemonics

	if(strcasecmp(chkInto,"Mnemonic")==0){    // check in Mnemonic table

		for(int i=0;i<=10;i++)
		{
			if(strcasecmp(chk,Mnemonic[i])==0)
				return true;
		}
			return false;
	}
	else if(strcasecmp(chkInto,"Register")==0){   // check in Register table
		
		for(int i=0;i<4;i++)
		{
			if(strcasecmp(chk,Register[i])==0)
				return true;
		}
			return false;
	}
	else if(strcasecmp(chkInto,"Condition")==0){	// check in Condition table
		
		for(int i=0;i<6;i++)
		{
			if(strcasecmp(chk,Condition[i])==0)
				return true;
		}
			return false;
	}
	else if(strcasecmp(chkInto,"Declarative")==0){		// check in Declarative table
		
		for(int i=0;i<2;i++)
		{
			if(strcasecmp(chk,Declarative[i])==0)
				return true;
		}
			return false;
	}
	else if(strcasecmp(chkInto,"AssemblyDir")==0){		// check in AssemblyDir table
		
		for(int i=0;i<5;i++)
		{
			if(strcasecmp(chk,AssemblyDir[i])==0)
				return true;
		}
			return false;
	}

	else if(strcasecmp(chkInto,"All")==0){		// check in All tables

		for(int i=0;i<11;i++)
		{
			if(strcasecmp(chk,Mnemonic[i])==0)
				return true;

			if(i<4)
				if(strcasecmp(chk,Register[i])==0)
					return true;

			if(i<6)	
				if(strcasecmp(chk,Condition[i])==0)
					return true;

			if(i<2)	
				if(strcasecmp(chk,Declarative[i])==0)
					return true;

			if(i<5)	
				if(strcasecmp(chk,AssemblyDir[i])==0)
					return true;
		}
			return false;
	}
}
