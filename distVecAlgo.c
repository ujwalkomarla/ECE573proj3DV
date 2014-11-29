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
	int i,j,k,t;
	int SELF;
	float ThroughI, old;
	int iNoOfNodes;
	int iNoOfLinks;
	if(0 == fscanf(pTopologyFile, "%d", &iNoOfNodes)) DieWithError("File Read: Topology file, Number of nodes");
	iNoOfLinks = CountLinesInFile(pTopologyFile);
	#ifdef DEBUGOLD
		printf("Number of links : %d\r\n",iNoOfLinks);
	#endif
	int *links = malloc(sizeof(int) * iNoOfLinks * 2); //2 -> Node1 Node2
	float *linkCost = malloc(sizeof(float) * iNoOfLinks);
	for(i=0; i<iNoOfLinks; i++ ){
		fscanf(pTopologyFile, "%d %d %f", (links + i*2 + 0), (links + i*2 + 1), (linkCost + i));
	#ifdef DEBUGOLD
		printf("Iteration %d : %d %d %f\r\n",i, *(links + i*2 + 0), *(links + i*2 + 1), *(linkCost + i));
	#endif
	}
	float *overallMatrix = malloc(sizeof(float) * iNoOfNodes * iNoOfNodes);
	//memset(overallMatrix, -1, sizeof(int) * iNoOfNodes * iNoOfNodes);// -1 not a neighbour
	for(i=0; i<iNoOfNodes*iNoOfNodes;i++) *(overallMatrix+i)=INFINITY;//-99.9; // NOT A NEIGHBOUR
	for(i=0; i<iNoOfLinks; i++){
		*(overallMatrix + (*(links + i*2 + 0)-1)*iNoOfNodes + *(links + i*2 + 1)-1) = *(linkCost + i);//Neighbours
		*(overallMatrix + (*(links + i*2 + 1)-1)*iNoOfNodes + *(links + i*2 + 0)-1) = *(linkCost + i);//Neighbours
	}
	for(i=0;i<iNoOfNodes;i++) *(overallMatrix + i*iNoOfNodes + i) = 0.0;//SELF
	#ifdef DEBUGOLD
	printf("  ");
	for(i=1;i<iNoOfNodes+1;i++) printf("%5d ", i);
	printf("\r\n");
	for(i=0;i<iNoOfNodes;i++){
		printf("%3d", i+1);	
		for(j=0;j<iNoOfNodes;j++)
			printf("%5.1f ", *(overallMatrix + i*iNoOfNodes + j));
		printf("\r\n");	
	}
	#endif
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	int x;
struct tNodeInfo{
	float *localNextNodeMatrix[iNoOfNodes];
	float *localNodeMatrix[iNoOfNodes];
	int neighbours[iNoOfNodes];
	
	int Update[iNoOfNodes];
	float *UpdateVector[iNoOfNodes];
}NodeInfo;
for(x=0;x<iNoOfNodes;x++){
	//x=7
	//Count number of neighbours for NODE x
	int tneighbours=0;
	for(i=0;i<iNoOfNodes;i++){
		if( INFINITY > *(overallMatrix + x*iNoOfNodes + i))//Neighbour
			tneighbours++;
	}
	//Replicate overallMatrix to node
	NodeInfo.localNodeMatrix[x] = malloc(sizeof(float) * tneighbours * (iNoOfNodes+1)); //+1 -> Store the neighbour node ID
	NodeInfo.localNextNodeMatrix[x] = malloc(sizeof(float)*iNoOfNodes);
	NodeInfo.neighbours[x] = tneighbours; 
	NodeInfo.UpdateVector[x] = malloc(sizeof(float)*iNoOfNodes);
	tneighbours=0;
	for(i=0;i<iNoOfNodes;i++){
		if( INFINITY > *(overallMatrix + x*iNoOfNodes + i)){//Neighbour
			*(NodeInfo.localNodeMatrix[x] + tneighbours*(iNoOfNodes+1)) = i;//i is the neighbour/self node id
			*(NodeInfo.localNextNodeMatrix[x] + i) = i;//SELF<-WRONG, Next HOP is expected
			if(i==x){ //SELF
				for(j=1;j<iNoOfNodes+1;j++){
					*(NodeInfo.localNodeMatrix[x] + tneighbours*(iNoOfNodes+1) + j) = *(overallMatrix + i*iNoOfNodes + (j-1));
					//if(INFINITY!=*(NodeInfo.localNodeMatrix[x] + tneighbours*(iNoOfNodes+1) + j))
					//*(NodeInfo.localNextNodeMatrix[x] + (j-1)) = 	
					*(NodeInfo.UpdateVector[x] + j-1) = *(NodeInfo.localNodeMatrix[x] + tneighbours*(iNoOfNodes+1) + j);
					
				}
				//NodeInfo.Update[i]=1;
			}else{
				for(j=1;j<iNoOfNodes+1;j++){
					*(NodeInfo.localNodeMatrix[x] + tneighbours*(iNoOfNodes+1) + j) = INFINITY;
				}
			}
			tneighbours++;
			
		}
		
	}
	
	#ifdef DEBUGOLD
	for(i=0;i<NodeInfo.neighbours[x];i++){
		printf("\r\nNODE %3.0f:",*(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)));
		for(j=1;j<iNoOfNodes+1;j++)
			printf("%5.1f ", *(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)+j));
	}
	printf("\r\n");
	
	/*for(i=0;i<iNoOfNodes;i++){
		printf("%d ", NodeInfo.Update[i]);
	}
	printf("\r\n");
	for(i=0;i<iNoOfNodes;i++) printf("%5.1f ",*(NodeInfo.UpdateVector[x] + i));
	printf("\r\n");*/
	#endif	
}	
	//exit(1);
	NodeInfo.Update[iInitNode]=1;
	int RUN = 1;
	while(RUN){
		for(i=0;i<iNoOfNodes;i++){//'i' -> The node which has sent an update message?
			
			if(1==NodeInfo.Update[i]){
				NodeInfo.Update[i]=0;
				for(j=0;j<iNoOfNodes;j++){//'j' -> Check if 'j' has 'i' as it's neighbour
					if(i==j) continue;
					for(k=0;k<NodeInfo.neighbours[j];k++){
						if(i==*(NodeInfo.localNodeMatrix[j] + k*(iNoOfNodes+1))){
							
							for(t=1;t<iNoOfNodes+1;t++){// 't' -> Link cost
								*(NodeInfo.localNodeMatrix[j] + k*(iNoOfNodes+1) + t) = *(NodeInfo.UpdateVector[i] + t - 1);
							}
							for(t=0;t<NodeInfo.neighbours[j];t++){
								if(j==*(NodeInfo.localNodeMatrix[j] + t*(iNoOfNodes+1))) {SELF = t; /*printf("SELF %d\r\n",t);*/break;}
							}
							for(t=1;t<iNoOfNodes+1;t++){
								ThroughI = *(NodeInfo.localNodeMatrix[j]+k*(iNoOfNodes+1)+t) + *(NodeInfo.localNodeMatrix[j]+SELF*(iNoOfNodes+1)+(i+1));
								old = *(NodeInfo.localNodeMatrix[j]+SELF*(iNoOfNodes+1)+t);
								if(ThroughI < old){
									*(NodeInfo.localNodeMatrix[j]+SELF*(iNoOfNodes+1)+t) = ThroughI;
									*(NodeInfo.localNextNodeMatrix[j] + t-1) =  i;
									
									NodeInfo.Update[j]=1;
								}
							}
							if(1==NodeInfo.Update[j]){
								for(t=0;t<iNoOfNodes;t++)
									*(NodeInfo.UpdateVector[j] + t)=*(NodeInfo.localNodeMatrix[j]+SELF*(iNoOfNodes+1)+t+1);
							}
							break;
						}
					}
				}	
			}
			
		}//for(i=0;i<iNoOfNodes;i++) NodeInfo.Update[i] = tUpdate[i];
	#ifdef DEBUGOLD
	for(x=0;x<iNoOfNodes;x++){
		for(i=0;i<NodeInfo.neighbours[x];i++){
			printf("\r\nNODE %3.0f:",*(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)));
			for(j=1;j<iNoOfNodes+1;j++)
				printf("%5.1f ", *(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)+j));
		}
		printf("\r\n");
	}
	break;
	#endif	
	
	#ifdef DEBUGOLD
	for(i=0;i<iNoOfNodes;i++){
		printf("%d ", NodeInfo.Update[i]);
	}
	printf("\r\n");
	#endif
		RUN=0;
		for(i=0;i<iNoOfNodes;i++){
			if(0!=NodeInfo.Update[i]) {RUN=1;break;}
		}
		
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		//-1 Human to Code indexing
for(t=0;t<NodeInfo.neighbours[iNode1-1];t++){
	if((iNode1-1)==*(NodeInfo.localNodeMatrix[iNode1-1] + t*(iNoOfNodes+1))) {SELF = t; /*printf("SELF %d\r\n",t);*/break;}
}	
printf("Cost from Node %d to Node %d : %f\r\n",iNode1,iNode2,*(NodeInfo.localNodeMatrix[iNode1-1]+SELF*(iNoOfNodes+1)+iNode2));



	
	
	
	#ifdef DEBUG
	for(x=0;x<iNoOfNodes;x++){
		if(x==(iNode1-1) || x==(iNode2-1)){
			for(i=0;i<NodeInfo.neighbours[x];i++){
				printf("\r\nNODE %3.0f:",*(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)) + 1);//+1 -> Code indexing to human
				for(j=1;j<iNoOfNodes+1;j++)
					printf("%5.1f, %2.1f ", *(NodeInfo.localNodeMatrix[x]+i*(iNoOfNodes+1)+j),*(NodeInfo.localNextNodeMatrix[x]+j-1));
			}
			printf("\r\n");
		}
	}
	
	#endif	


return 0;
}