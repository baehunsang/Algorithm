#include<stdio.h>
/*Assignment for algorithm(COSE 214 -01)
 Computing single source shortest distances of a directed weighted graph.

 Working environment: Visual studio 2019
 */
#define INF 999

void Dijkstra(int** dstmatrix, int outputArr[], int numOfNode, int startNode) {
	int* table = (int*)malloc(sizeof(int) * numOfNode);
	int minValue = INF;
	int minVertex;
	for (int i = 0; i < numOfNode; i++) {
		table[i] = 0;
	}
	table[startNode] = 1; //S = {startnode}

	for (int i = 0; i < numOfNode; i++) {
		outputArr[i] = dstmatrix[startNode][i]; //Initialize output array.
	}
	for (int i = 0; i < numOfNode; i++) {
		for (int j = 0; j < numOfNode; j++) {
			if (table[j] == 0) {
				if (outputArr[j] < minValue) {
					minValue = outputArr[j];
					minVertex = j;
				}
			}
		}
		table[minVertex] = 1; //Choose a vertex in V - S such that outputArr[j] is minimum and add to S.
		for (int j = 0; j < numOfNode; j++) {
			if (table[j] == 0) {// Each vertex in V - S
				outputArr[j] = min(outputArr[j], outputArr[minVertex] + dstmatrix[minVertex][j]);
			}
		}
		minValue = INF;
	}
	free(table);
}

int min(int a, int b) {
	if (a > b) {
		return b;
	}
	return a;
}
int main() {
	int numOfGraph;
	int startNode;
	printf("Enter the number of graph\n");
	scanf("%d", &numOfGraph);
	for (int i = 0; i < numOfGraph; i++) {
		int numOfNode;
		printf("Enter the number of node\n");
		scanf("%d", &numOfNode);

		int** dstmatrix = (int**)malloc(sizeof(int*) * numOfNode);
		for (int i = 0; i < numOfNode; i++) {
			dstmatrix[i] = (int*)malloc(sizeof(int) * numOfNode);
		}
		int* outputArr = (int*)malloc(sizeof(int) * numOfNode);

		printf("Enter the distance between each nodes\n");
		printf("If you don't know, enter 0\n");
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				scanf("%d", &dstmatrix[i][j]);
			}
		}// Get the distance between each nodes.
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				if (i != j && dstmatrix[i][j] == 0) {
					dstmatrix[i][j] = INF;
				}
			}
		} // Initialize the distance matrix.

		printf("Choose start node\n");
		scanf("%d", &startNode);

		Dijkstra(dstmatrix, outputArr, numOfNode, startNode);
		
		printf("Shortest distances from node %d\n", startNode);
		printf("-----------------------------\n"); printf("   node |");
		for (int i = 0; i < numOfNode; i++) {
			printf("%3d|", i); // Output array's 'i'th element means shortest distance between stary node to node 'i'.
		}
		printf("\n");
		printf("-----------------------------\n"); printf("distence|");
		for (int i = 0; i < numOfNode; i++) {
			printf("%3d|", outputArr[i]); // Output array's 'i'th element means shortest distance between stary node to node 'i'.
		}
		printf("\n");
		for (int i = 0; i < numOfNode; i++) {
			free(dstmatrix[i]);
		}
		free(dstmatrix);
		free(outputArr);
	}
}