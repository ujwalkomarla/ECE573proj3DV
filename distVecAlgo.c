#include"customDefinitions.h"


int main(int argc,char **argv){
	if (5 != argc) {
		char *str;
		sprintf(str,"USAGE: %s initial-node file-name node1 node2",argv[0]);
		DieWithError(str);
	}
	FILE *pTopologyFile = fopen(argv[2],"r");
	int iInitNode = atoi(argv[1]);
	int iNode1 = atoi(argv[3]);
	int iNode2 = atoi(argv[4]);
	int i,j;
	int iNoOfNodes;
	int iNoOfLinks;
	if(0 == fscanf(pTopologyFile, "%d", &iNoOfNodes)) DieWithError("File Read: Topology file, Number of nodes");
	iNoOfLinks = CountLinesInFile(pTopologyFile);
	#ifdef DEBUG
		printf("Number of links : %d\r\n",iNoOfLinks);
	#endif
	int *links = malloc(sizeof(int) * iNoOfLinks * 2); //2 -> Node1 Node2 
	float *linkCost = malloc(sizeof(float) * iNoOfLinks);
	for(i=0; i<iNoOfLinks; i++ ){
		fscanf(pTopologyFile, "%d %d %f", (links + i*3 + 0), (links + i*3 + 1), (linkCost + i));
	#ifdef DEBUG
		printf("Iteration %d : %d %d %f\r\n",i, *(links + i*3 + 0), *(links + i*3 + 1), *(linkCost + i));
	#endif
	}
	float *overallMatrix = malloc(sizeof(float) * iNoOfNodes * iNoOfNodes);
	memset(overallMatrix, 0 , sizeof(float) * iNoOfNodes * iNoOfNodes);// -1 not a neighbour
	for(i=0; i<iNoOfLinks; i++){
		*(overallMatrix + (*(links + i*3 + 0)-1)*iNoOfNodes + *(links + i*3 + 1)-1) = *(linkCost+i);//Neighbours
		*(overallMatrix + (*(links + i*3 + 1)-1)*iNoOfNodes + *(links + i*3 + 0)-1) = *(linkCost+i);//Neighbours
	}
	for(i=0;i<iNoOfNodes;i++) *(overallMatrix + i*iNoOfNodes + i) = 0;
	#ifdef DEBUG
	printf("   ");
	for(i=1;i<iNoOfNodes+1;i++) printf("%4d ", i);
	printf("\r\n");
	for(i=0;i<iNoOfNodes;i++){
		printf("%4d", i+1);	
		for(j=0;j<iNoOfNodes;j++)
			printf("%4.1f ", *(overallMatrix + i*iNoOfNodes + j));
		printf("\r\n");	
	}
	#endif


return 0;
}