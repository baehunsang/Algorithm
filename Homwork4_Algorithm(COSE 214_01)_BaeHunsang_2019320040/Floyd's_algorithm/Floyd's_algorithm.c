#include<stdio.h>
/*Assignment for algorithm(COSE 214 -01)
 Computing all pairs of shortest distance in derected graph

 Working environment: Visual studio 2019
 */
#define INF 999

void Floyd(int** dstmarix, int numOfNode) {
	for (int k = 0; k < numOfNode; k++) {
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				dstmarix[i][j] = min(dstmarix[i][j], dstmarix[i][k] + dstmarix[k][j]);
			}
		}
	}
}

int min(int a, int b) {
	if (a > b) {
		return b;
	}
	return a;
}
int main() {
	int numOfGraph;
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

		Floyd(dstmatrix, numOfNode);

		printf("All pairs of shortest destance is\n");
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				printf("%3d ", dstmatrix[i][j]);
			}
			printf("\n");
		}

		for (int i = 0; i < numOfNode; i++) {
			free(dstmatrix[i]);
		}
		free(dstmatrix);
	}
}