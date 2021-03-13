/***************** Abbrevations Used ******************
1. op --> operand
2. LC --> Location Counter
*******************************************************/

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>
#include "dataStructures.c"

#define newError (Error*)malloc(sizeof(Error))

void findError(int);
void printErrors();
void addError(int, char[]);
bool check(char[],char[]);

char fileName[20],op1[20],op2[20],op3[20],op4[20];
int lineCount=0,LC=0,noOftokens=0;


int main(int argc, char *argv[]){

	if(argc==1){
		printf("\nEnter the program file name : ");
		scanf("%s",fileName);
	}
	else
		strcpy(fileName,argv[1]);

	FILE *ptr= fopen(fileName,"r+");

	if(ptr==NULL)
		printf("\nError.....{file not found}");

	char line[80];
	while((fgets(line,80,ptr))!=NULL){
		lineCount++;
		if(lineCount==1)
		{
			sscanf(line,"%s%s%s%s",op1,op2,op3,op4);
			if(strcasecmp(op1,"START")==0 || strcasecmp(op1,"ORIGIN")==0){
				LC=atoi(op2);         // Initializing LC Counter
				LC--;				//Decreasing LC so that LC start from the next line to the START
			}
		}
	}
	fclose(ptr);

	findError(lineCount);
	printErrors();
}

#include "errors.c"

