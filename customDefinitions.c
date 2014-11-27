#include"customDefinitions.h"

void DieWithError(char *msg){
	fprintf(stderr, "ERROR \n%s", msg);
	exit(1);
}

int CountLinesInFile(FILE *fp){
	int lines = 0;
	char ch;
	fpos_t pos;
	fgetpos(fp, &pos);
	while(!feof(fp))
	{
		//Though, fgetc needs a int type return value,
		//we haven't, as we do an EOF check in the loop condition.
	  ch = fgetc(fp);
	  if(ch == '\n')
		lines++;
	}
	fsetpos(fp,&pos);
	return lines;
}