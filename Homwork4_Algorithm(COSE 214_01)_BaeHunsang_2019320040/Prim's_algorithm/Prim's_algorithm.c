/*Assignment for algorithm(COSE 214 -01)
 Computing MST with input adjacency matrix.
 Prim's algorithm

 Working environment: Visual studio 2019
*/

/*The array 'MstNode' means each nodes in MST for input graph.
  if MstNode[i] == 1, then the node 'i' is in MST for input graph.
  The information of distance between MST to other nodes is in the array 'distance'.
  The root node of MST is the node 0.
*/

#include <stdio.h>
#include <stdlib.h>

#define INF 9999

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

/*Insert function: return 1 -> Fail to insert
                   return 0 -> Success to insert*/
int InsertEdge(Head* head, int srt, int dst, int weight) {
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

void MstPrim(int** dstMatrix, Head* MST, int numOfNode) {
    int srt, dst;
    int* MstNode = (int*)malloc(sizeof(int) * numOfNode);
    int* distance = (int*)malloc(sizeof(int) * numOfNode);
    int* parent = (int*)malloc(sizeof(int) * numOfNode);//parent[i] means the parent node of the node 'i'.
    distance[0] = 0;
    MstNode[0] = 1;// Initialize the root node.

    for (int i = 1; i < numOfNode; i++) {
        distance[i] = dstMatrix[0][i];
        parent[i] = 0;
        MstNode[i] = 0;
    }// Initialize information

    for (int i = 0; i < numOfNode - 1; i++) {
        dst=MinIndex(distance, numOfNode, MstNode);
        srt = parent[dst];
        InsertEdge(MST, srt, dst, distance[dst]);
        MstNode[dst] = 1;

        for (int j = 1; j < numOfNode; j++) {// Update the distance of path between MST and other nodes.
            if (MstNode[j] == 0 && dstMatrix[j][dst] < distance[j]) {
                distance[j] = dstMatrix[j][dst];
                parent[j] = dst;
            }
        }
    }
    free(MstNode);
    free(distance);
    free(parent);
}

/*Return the index of minimum value.
  It is used instead of EXTRACT_MIN because this implementation use two array instead of a priority queue.*/
int MinIndex(int arr[], int len, int MstNode[]) {
    int min = INF;
    int index;
    for (int i = 0; i < len; i++) {
        if (MstNode[i] == 0 && arr[i]<min) {
            min = arr[i];
            index = i;
        }
    }
    return index;
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
        Head* MST = CreatHead();

        printf("Enter the adjacency matrix\n");
        for (int i = 0; i < numOfNode; i++) {
            for (int j = 0; j < numOfNode; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        for (int i = 0; i < numOfNode; i++) {
            for (int j = 0; j < numOfNode; j++) {
                if (i != j && matrix[i][j] == 0) {
                    matrix[i][j] = INF;
                }
            }
        } // Initialize the distance matrix.

        MstPrim(matrix, MST, numOfNode);


        printf("\nEdges of MST\n");
        printf("----------------\n");
        printf("|Start |End    |\n");
        printf("----------------\n");
        for (int i = 0; i < MST->count; i++) {
            printf("|%3d   |%3d    |\n", (MST->edgeList)[i].srt, (MST->edgeList)[i].dst);
            printf("----------------\n");
        }

        DeleteHead(MST);
        for (int i = 0; i < numOfNode; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}