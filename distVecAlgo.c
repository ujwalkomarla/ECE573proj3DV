#include"customDefinitions.h"


int main(int argc,char **argv){
	if (5 != argc) {
		char *str;
		sprintf(str,"USAGE: %s initial-node file-name node1 node2",argv[0]);
		DieWithError(str);
	}
	const FILE *pTopologyFile = fopen(argv[2],"r");
	const int iInitNode = atoi(argv[1]);
	const int iNode1 = atoi(argv[3]);
	const int iNode2 = atoi(argv[4]);

	int iNoOfNodes;
	int iNoOfLinks;
	if(0 == fscanf(pTopologyFile, "%d", &iNoOfNodes)) DieWithError("File Read: Topology file, Number of nodes");
	iNoOfLinks = CountLinesInFile(pTopologyFile);
	#ifdef DEBUG
		printf("Number of links : %d\r\n",iNoOfLinks);
	#endif



return 0;
}