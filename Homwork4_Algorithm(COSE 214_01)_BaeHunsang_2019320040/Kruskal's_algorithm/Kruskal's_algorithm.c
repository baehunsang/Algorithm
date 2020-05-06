/*Assignment for algorithm(COSE 214 -01)
 Computing MST with input adjacency matrix.
 Kruskal's algorithm

 Working environment: Visual studio 2019
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int srt; //Start node
	int dst; // End node
	int weight;
}edge;  // Struct for MST's each edge.

typedef struct {
	edge* edgeList;
	int count; // Number of elements of list
}Head;
// Head structure for the edge list.

Head* CreatHead() {
	Head* newHead = (Head*)malloc(sizeof(Head));
	newHead->edgeList = NULL;
	newHead->count = 0;
	return newHead;
}

void DeleteHead(Head* head) {
	free(head->edgeList);
	free(head);
}

//Compare function for quick sort.
int compare(const void* n1, const void* n2) {
	if (((edge*)n1)->weight > ((edge*)n2)->weight) {
		return 1;
	}
	else if (((edge*)n1)->weight == ((edge*)n2)->weight) {
		return 0;
	}
	else {
		return -1;
	}
}

/*Insert function: return 1 -> Fail to insert
                   return 0 -> Success to insert*/
int InsertEdge(Head* head,int srt, int dst, int weight) {
	if (head->count == 0) {
		head->edgeList = (edge*)malloc(sizeof(edge));
	}
	else {
		head->edgeList = (edge*)realloc(head->edgeList, sizeof(edge) * ((head->count) + 1));
	}
	if (!(head->edgeList)) {
		return 1;
	}
	(head->edgeList)[head->count].srt = srt;
	(head->edgeList)[head->count].dst = dst;
	(head->edgeList)[head->count].weight = weight;
	head->count++;
	return 0;
}

/*Find function returns a representative number of the disjoint set.
  The array 'belong' contains a representative number for each index.*/
int Find(int belong[], int nodeNo) {
	return belong[nodeNo];
}
/*Unite disjoint set by changing the representative number in 'belong' array.*/
void Union(int belong[], int numOfNode, int indent1, int ident2) {
	for (int i = 0; i < numOfNode; i++) {
		if (belong[i]==ident2) {
			belong[i] = indent1;
		}
	}
}

void MakeSet(int belong[], int numOfNode) {
	for (int i = 0; i < numOfNode; i++) {
		belong[i] = i;
	}
}

void MstKruskal(Head* E, Head* MST, int numOfNode) {
	int ident1, ident2;
	int* belong = (int*)malloc(sizeof(int) * numOfNode);
	MakeSet(belong, numOfNode);

	qsort(E->edgeList, E->count, sizeof(edge), compare);

	for (int i = 0; i < E->count; i++) {// For each edges in E
		ident1 = Find(belong,(E->edgeList)[i].srt);
		ident2 = Find(belong,(E->edgeList)[i].dst);
		if (ident1 != ident2) {
			InsertEdge(MST, (E->edgeList)[i].srt, (E->edgeList)[i].dst, (E->edgeList)[i].weight);
			Union(belong, numOfNode, ident1, ident2);
		}
	}
	free(belong);
}



int main() {
	int numOfGraph;
	printf("Enter the number of graph\n");
	scanf("%d", &numOfGraph);
	for (int i = 0; i < numOfGraph; i++) {
		int numOfNode;
		printf("Enter the number of node\n");
		scanf("%d", &numOfNode);

		int** matrix = (int**)malloc(sizeof(int*) * numOfNode);
		for (int i = 0; i < numOfNode; i++) {
			matrix[i] = (int*)malloc(sizeof(int) * numOfNode);
		}
		Head* setOfEdge = CreatHead();
		Head* MST = CreatHead();
		
		printf("Enter the adjacency matrix\n");
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				scanf("%d", &matrix[i][j]);
			}
		}
		for (int i = 0; i < numOfNode; i++) {
			for (int j = 0; j < numOfNode; j++) {
				if (matrix[i][j] != 0) {
					InsertEdge(setOfEdge, i, j, matrix[i][j]);
				}
			}
		}

		MstKruskal(setOfEdge, MST, numOfNode);

		printf("\nEdges of MST\n");
		printf("----------------\n");
		printf("|Start |End    |\n");
		printf("----------------\n");
		for (int i = 0; i < MST->count; i++) {
			printf("|%3d   |%3d    |\n", (MST->edgeList)[i].srt, (MST->edgeList)[i].dst);
			printf("----------------\n");
		}

		DeleteHead(setOfEdge);
		DeleteHead(MST);
		for (int i = 0; i < numOfNode; i++) {
			free(matrix[i]);
		}
		free(matrix);
	}
}