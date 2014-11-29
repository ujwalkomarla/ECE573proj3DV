#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<float.h>
#define DEBUG
#ifdef DEBUG 
	#define INFINITY 99.9
#else
	#define INFINITY FLT_MAX
#endif	
void DieWithError(char *);
int CountLinesInFile(FILE *fp);