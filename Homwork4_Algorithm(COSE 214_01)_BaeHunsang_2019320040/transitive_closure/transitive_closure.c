#include <stdio.h>
/*Assignment for Algorithm(COSE 214 - 01)
 Computing transitive closure for directed graph
 
 Working environment: Visual studio 2019*/

void Warshell(int** R, int numOfNode) {
	/*Input: N demensional adjacency matrix
	  Output: Transitive closure of that graph*/
	for (int k = 0; k < numOfNode; k++) {
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				R[i][j] = R[i][j] | (R[i][k] & R[k][j]);
			}
		}
	}
}

int main() {
	int numOfGraph;
	printf("Enter the number of Graph\n");
	scanf("%d", &numOfGraph);
	for (int i = 0; i < numOfGraph; i++) {
		int numOfNode;
		printf("Enter the numder of node\n");
		scanf("%d", &numOfNode);

		int** adjMatrix = (int**)malloc(sizeof(int*) * numOfNode);
		for (int i = 0; i < numOfNode; i++) {
			adjMatrix[i] = (int*)malloc(sizeof(int) * numOfNode);
		} // Allocate memory space.

		printf("Enter the adjacency matrix\n");
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				scanf("%d", &adjMatrix[i][j]);
			}
		} //Initialize the adjacency matrix.

		Warshell(adjMatrix, numOfNode);

		printf("The transitive closure of input graph is\n");
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				printf("%d ", adjMatrix[i][j]);
			}
			printf("\n");
		} //Print transitive closure.

		for (int i = 0; i < numOfNode; i++) {
			free(adjMatrix[i]);
		} // Free memory space.
		free(adjMatrix);
	}
}
